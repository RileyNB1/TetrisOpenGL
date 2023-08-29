#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <cstdlib>
//#include <OpenGLApp.h>
//#include <managers/GameManager.h>

#define MAX_RAY_DEPTH 100
#define PI 3.1415926535

//vector 3
struct Vector3
{
public:
	float x, y, z;
	Vector3() : x(0), y(0), z(0) {}
	Vector3(float xx) : x(xx), y(xx), z(xx) {}
	Vector3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}

	Vector3& normalize() {
		float nor2 = length2();
		if (nor2 > 0) {
			float invNor = 1 / sqrt(nor2);
			x *= invNor, y *= invNor, z *= invNor;
		}
		return *this;
	}

	Vector3 operator * (const float& f) const {
		return Vector3(x * f, y * f, z * f);
	}

	Vector3 operator * (const Vector3& v) const {
		return Vector3(x * v.x, y * v.y, z * v.z);
	}

	float dot(const Vector3& v) const {
		return x * v.x + y * v.y + z * v.z;
	}

	Vector3 operator - (const Vector3& v) const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator + (const Vector3& v) const {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3& operator += (const Vector3& v) {
		x += v.x, y += v.y, z += v.z; return *this;
	}

	Vector3& operator *= (const Vector3& v) {
		x *= v.x, y *= v.y, z *= v.z; return *this;
	}

	Vector3 operator - () const {
		return Vector3(-x, -y, -z);
	}

	float length2() const {
		return x * x + y * y + z * z;
	}

	float length() const {
		return sqrt(length2());
	}

	friend std::ostream& operator << (std::ostream& os, const Vector3& v) {
		os << "[" << v.x << " " << v.y << " " << v.z << "]";
		return os;
	}
};

class Sphere {
public:
	float radius, radiusSqr;
	float transparency, reflection;
	Vector3 center;
	Vector3 surfaceColor, emissionColor;

	Sphere(const Vector3& c, const float& r, const Vector3& sc, const float& refl,
		const float& transp, const Vector3& ec)
		: center(c), radius(r), radiusSqr(r* r), surfaceColor(sc), emissionColor(ec),
		transparency(transp), reflection(refl) { }

	bool Intersect(const Vector3& rayOrigin, const Vector3& rayVector, float& p1,
		float& p2) const {
		Vector3 lengthOfRay = center - rayOrigin;
		float tc = lengthOfRay.dot(rayVector);
		if (tc < 0)
		{
			// sphere is in opposite direction of from ray origin vs ray vector
			return false;
		}

		float rayDistanceFromShereSqr = lengthOfRay.dot(lengthOfRay) - tc * tc;

		if (rayDistanceFromShereSqr > radiusSqr)
		{
			return false;
		}

		float t1c = sqrt(radiusSqr - rayDistanceFromShereSqr);
		p1 = tc - t1c;
		p2 = tc + t1c;

		return true;
	}
};

class RayTracer
{
public:
	float Mix(const float& x, const float& y, const float& mix);

	Vector3 Trace(
		const Vector3& origin,
		const Vector3& direction,
		const std::vector<Sphere>& spheres,
		const int& depth);

	void Render(const std::vector<Sphere>& spheres);
};

float RayTracer::Mix(const float& x, const float& y, const float& mix) {
	return y * mix + x * (1 - mix);
}

Vector3 RayTracer::Trace(const Vector3& origin, const Vector3& direction,
	const std::vector<Sphere>& spheres, const int& depth) {
	float tnear = INFINITY;
	const Sphere* sphere = NULL;
	for (unsigned i = 0; i < spheres.size(); ++i) {
		float p1 = INFINITY, p2 = INFINITY;
		if (spheres[i].Intersect(origin, direction, p1, p2)) {
			if (p1 < 0) {
				p1 = p2;
			}
			if (p1 < tnear) {
				tnear = p1;
				sphere = &spheres[i];
			}
		}
	}
	if (!sphere)
		return Vector3(2);

	Vector3 surfaceColor = 0; // color of the surface of object intersected by the ray
	Vector3 phit = origin + (direction * tnear); // point of intersection
	Vector3 nhit = phit - sphere->center; // normal at the intersection point

	nhit.normalize(); // normalize normal direction
	float bias = 1e-4; // add some bias to the point from which we will be tracing
	bool inside = false;

	if (direction.dot(nhit) > 0)
	{
		nhit = -nhit, inside = true;
	}

	if ((sphere->transparency > 0 || sphere->reflection > 0) &&
		depth < MAX_RAY_DEPTH)
	{

		float facingRatio = -direction.dot(nhit);
		float fresneleffect = Mix(pow(1 - facingRatio, 3), 1, 0.1);
		// compute reflection direction
		Vector3 refldir = direction - nhit * 2 * direction.dot(nhit);
		refldir.normalize();
		Vector3 reflection = Trace(phit + nhit * bias, refldir, spheres, depth + 1);
		Vector3 refraction = 0;
		// if the sphere is also transparent compute refraction ray (transmission)

		if (sphere->transparency) {
			float ior = 1.1, eta = (inside) ? ior : 1 / ior; // inside or outside?
			float cosi = -nhit.dot(direction);
			float k = 1 - eta * eta * (1 - cosi * cosi);
			Vector3 refrdir = direction * eta + nhit * (eta * cosi - sqrt(k));
			refrdir.normalize();
			refraction = Trace(phit - nhit * bias, refrdir, spheres, depth + 1);
		}
		// result is reflection/refraction mix (if sphere is transparent)
		surfaceColor = (reflection * fresneleffect +
			refraction * (1 - fresneleffect) * sphere->transparency) *
			sphere->surfaceColor;
	}
	else {
		for (unsigned i = 0; i < spheres.size(); ++i) {
			if (spheres[i].emissionColor.x > 0) {
				// this is a light
				Vector3 transmission = 1;
				Vector3 lightDirection = spheres[i].center - phit;
				lightDirection.normalize();
				for (unsigned j = 0; j < spheres.size(); ++j) {
					if (i != j) {
						float p1, p2;
						if (spheres[j].Intersect(phit + nhit * bias, lightDirection,
							p1, p2)) {
							transmission = 0;
							break;
						}
					}
				}
				surfaceColor += sphere->surfaceColor * transmission *
					std::max(float(0), nhit.dot(lightDirection)) *
					spheres[i].emissionColor;
			}
		}
	}
	return surfaceColor + sphere->emissionColor;
}

void RayTracer::Render(const std::vector<Sphere>& spheres) {
	unsigned width = 400, height = 300;

	Vector3* image = new Vector3[width * height], * pixel = image;

	float invWidth = 1 / float(width), invHeight = 1 / float(height);
	float fov = 30, aspectratio = width / float(height);
	float angle = tan(PI * 0.5 * fov / 180.);
	// Trace rays
	for (unsigned y = 0; y < height; ++y) {
		for (unsigned x = 0; x < width; ++x, ++pixel) {


			float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
			float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
			Vector3 raydir(xx, yy, -1);
			raydir.normalize();
			*pixel = Trace(Vector3(0), raydir, spheres, 0);
			std::cout << y << "," << x <<(*pixel) <<"," <<*(pixel+1) << "," << *(pixel + 2) << std::endl;
		}
	}
	// Save result to a PPM image (keep these flags if you compile under Windows)
	std::ofstream ofs("./untitled.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << width << " " << height << "\n255\n";
	for (unsigned i = 0; i < width * height; ++i) {
		ofs << (unsigned char)(std::min(float(1), image[i].x) * 255) <<
			(unsigned char)(std::min(float(1), image[i].y) * 255) <<
			(unsigned char)(std::min(float(1), image[i].z) * 255);
	}
	ofs.close();
	delete[] image;
}

int main()
{
    /*FOGrP::OpenGLApp app;

    app.Start();

    return 0;*/

    /*GameManager* game = GameManager::Instance();
        game->Run();
        GameManager::Release(); 
        game = nullptr; 
        return 0;*/

    srand(13);
    RayTracer* tracer = new RayTracer();
    std::vector<Sphere> spheres;
    
    // position, radius, surface color, reflectivity, transparency, emission color
    spheres.push_back(Sphere(
        Vector3(0.0, -40, -20), 
        10000,
        Vector3(0.20, 0.20, 0.20), 
        0, 0.0, Vector3(3)));
    spheres.push_back(Sphere(Vector3(0.0, 0, -20), 4,
        Vector3(1.00, 0.32, 0.36), 1, 0.5, Vector3(3)));
    spheres.push_back(Sphere(Vector3(5.0, -1, -15), 2,
        Vector3(0.90, 0.76, 0.46), 1, 0.0, Vector3(3)));
    /*spheres.push_back(Sphere(Vector3(5.0, 0, -25), 3,
        Vector3(0.65, 0.77, 0.97), 1, 0.0, Vector3(3)));
    spheres.push_back(Sphere(Vector3(-5.5, 0, -15), 3,
        Vector3(0.90, 0.90, 0.90), 1, 0.0, Vector3(3)));*/

    // light
    spheres.push_back(Sphere(Vector3(0.0, 20, -30), 3,
        Vector3(0.00, 0.00, 0.00), 0, 0.0, Vector3(3)));
    
    tracer->Render(spheres);
    
    return 0;
}