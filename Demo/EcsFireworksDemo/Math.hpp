#pragma once

namespace usagi {

	template <typename T> constexpr T M_E = T(2.71828182845904523536);       // e
	template <typename T> constexpr T M_LOG2E = T(1.44269504088896340736);       // log2(e)
	template <typename T> constexpr T M_LOG10E = T(0.434294481903251827651);      // log10(e)
	template <typename T> constexpr T M_LN2 = T(0.693147180559945309417);      // ln(2)
	template <typename T> constexpr T M_LN10 = T(2.30258509299404568402);       // ln(10)
	template <typename T> constexpr T M_PI = T(3.14159265358979323846);       // pi
	template <typename T> constexpr T M_PI_2 = T(1.57079632679489661923);       // pi/2
	template <typename T> constexpr T M_PI_4 = T(0.785398163397448309616);      // pi/4
	template <typename T> constexpr T M_1_PI = T(0.318309886183790671538);      // 1/pi
	template <typename T> constexpr T M_2_PI = T(0.636619772367581343076);      // 2/pi
	template <typename T> constexpr T M_2_SQRTPI = T(1.12837916709551257390);       // 2/sqrt(pi)
	template <typename T> constexpr T M_SQRT2 = T(1.41421356237309504880);       // sqrt(2)
	template <typename T> constexpr T M_SQRT1_2 = T(0.707106781186547524401);      // 1/sqrt(2)
	template <typename T> constexpr T M_180_DEGS = T(180);                          // 180 degrees

	template<typename T>
	struct Vector3 {
		Vector3() = default;

		Vector3(const T& x, const T& y, const T& z) :
			mX(x), mY(y), mZ(z) {}

		Vector3 operator+ (const Vector3& other) const {
			return { mX + other.mX, mY + other.mY, mZ + other.mZ };
		}

		Vector3 operator- (const Vector3& other) const {
			return { mX - other.mX, mY - other.mY, mZ - other.mZ };
		}

		Vector3 operator* (const T& value) const {
			return { mX * value, mY * value, mZ * value };
		}

		Vector3 operator/ (const T& value) const {
			return { mX / value, mY / value, mZ / value };
		}

		Vector3& operator+= (const Vector3& other) {
			mX += other.mX; mY += other.mY; mZ += other.mZ;

			return *this;
		}

		T x() const { return mX; }

		T y() const { return mY; }

		T z() const { return mZ; }
	private:
		T mX, mY, mZ;
	};

	template<typename T>
	struct Vector2 {
		Vector2() = default;

		Vector2(const T& x, const T& y) :
			mX(x), mY(y) {}

		Vector2 operator+ (const Vector2& other) const {
			return { mX + other.mX, mY + other.mY };
		}

		Vector2 operator- (const Vector2& other) const {
			return { mX - other.mX, mY - other.mY };
		}

		Vector2 operator* (const T& value) const {
			return { mX * value, mY * value };
		}

		Vector2 operator/ (const T& value) const {
			return { mX / value, mY / value };
		}

		Vector2& operator+= (const Vector2& other) {
			mX += other.mX; mY += other.mY;

			return *this;
		}

		T x() const { return mX; }

		T y() const { return mY; }
	private:
		T mX, mY;
	};

	template <typename T>
	Vector2<T> cubicBezier(
		const Vector2<T>& c0,
		const Vector2<T>& c1,
		const Vector2<T>& c2,
		const Vector2<T>& c3,
		T t)
	{
		// https://www.geeksforgeeks.org/cubic-bezier-curve-implementation-in-c/
		T xu = 0, yu = 0;
		xu = std::pow(1 - t, 3) * c0.x()
			+ 3 * t * std::pow(1 - t, 2) * c1.x()
			+ 3 * std::pow(t, 2) * (1 - t) * c2.x()
			+ std::pow(t, 3) * c3.x();
		yu = std::pow(1 - t, 3) * c0.y()
			+ 3 * t * std::pow(1 - t, 2) * c1.y()
			+ 3 * std::pow(t, 2) * (1 - t) * c2.y()
			+ std::pow(t, 3) * c3.y();
		return { xu, yu };
	}
	
	template <typename T>
	T cssCubicBezier(T x1, T y1, T x2, T y2, T t)
	{
		return cubicBezier<T>(
			{ 0, 0 },
			{ x1, y1 },
			{ x2, y2 },
			{ 1, 1 },
			t
			).y();
	}

	using Vector3f = Vector3<float>;
	using Vector2f = Vector2<float>;
	
}