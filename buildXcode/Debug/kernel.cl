#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#define EPS 1e-4f

__kernel void mandelbrot(
	__global uchar4 *imageData,
	__global float4 *colors,
	double zoom,
	double shiftX,
	double shiftY,
	int mouseX,
	int mouseY,
	int imageWidth,
	int imageHeight,
	int maxIteration,
	int colorsNum) {

	int x = get_global_id(0);
	int y = get_global_id(1);
	if (x >= imageWidth || y >= imageHeight) {
		return;
	}

	double2 c = (double2)((2.0 * y / imageWidth - 1.0) / zoom + shiftY,
						(2.0 * x / imageHeight - 1.0) / zoom + shiftX);
	double2 z = (double2)(0.0);
	double2 zSquares = (double2)(0.0);
	int iteration = 0;

	while (zSquares.x + zSquares.y < 1000.0 && iteration < maxIteration) {
		iteration++;
		z.y = 2.0 * z.y * z.x;
		z.x = zSquares.x - zSquares.y;
		z += c.yx;
		zSquares = z * z;
	}
	float mu = ((float)iteration - log(log(zSquares.x + zSquares.y) * 0.5) / log(2.0f)) / 10.0f;
	int integerPart = (int)mu % colorsNum;
	float fractPart = fmod(mu, 1.0f);

	const float3 bottomColor = colors[integerPart].xyz;
	const float3 topColor = colors[(integerPart + 1) % colorsNum].xyz;

	uchar3 color = convert_uchar3(mix(bottomColor, topColor, fractPart) * 255.0f);

	imageData[x + y * imageWidth] = (uchar4)(color.zyx, 0);
}

__kernel void perp1(
__global uchar4 *imageData,
__global float4 *colors,
double zoom,
double shiftX,
double shiftY,
int mouseX,
int mouseY,
int imageWidth,
int imageHeight,
int maxIteration,
int colorsNum) {

	int x = get_global_id(0);
	int y = get_global_id(1);
	if (x >= imageWidth || y >= imageHeight) {
		return;
	}

	double2 c = (double2)((2.0 * y / imageWidth - 1.0) / zoom + shiftY,
	(2.0 * x / imageHeight - 1.0) / zoom + shiftX);
	double2 z = (double2)(0.0);
	double2 zSquares = (double2)(0.0);
	int iteration = 0;

	while (zSquares.x + zSquares.y < 1000.0 && iteration < maxIteration) {
		iteration++;
		z.y = -2.0 * z.y * fabs(z.x);
		z.x = zSquares.x - zSquares.y;
		z += c.yx;
		zSquares = z * z;
	}
	float mu = ((float)iteration - log(log(zSquares.x + zSquares.y) * 0.5) / log(2.0f)) / 10.0f;
	int integerPart = (int)mu % colorsNum;
	float fractPart = fmod(mu, 1.0f);

	const float3 bottomColor = colors[integerPart].xyz;
	const float3 topColor = colors[(integerPart + 1) % colorsNum].xyz;

	uchar3 color = convert_uchar3(mix(bottomColor, topColor, fractPart) * 255.0f);

	imageData[x + y * imageWidth] = (uchar4)(color.zyx, 0);
}

__kernel void perp2(
__global uchar4 *imageData,
__global float4 *colors,
double zoom,
double shiftX,
double shiftY,
int mouseX,
int mouseY,
int imageWidth,
int imageHeight,
int maxIteration,
int colorsNum) {

	int x = get_global_id(0);
	int y = get_global_id(1);
	if (x >= imageWidth || y >= imageHeight) {
		return;
	}

	double2 c = (double2)((2.0 * y / imageWidth - 1.0) / zoom + shiftY,
	(2.0 * x / imageHeight - 1.0) / zoom + shiftX);
	double2 z = (double2)(0.0);
	double2 zSquares = (double2)(0.0);
	int iteration = 0;

	while (zSquares.x + zSquares.y < 1000.0 && iteration < maxIteration) {
		iteration++;
		z.y = -2.0 * z.y * fabs(z.x);
		z.x = fabs(zSquares.x - zSquares.y);
		z += c.yx;
		zSquares = z * z;
	}
	float mu = ((float)iteration - log(log(zSquares.x + zSquares.y) * 0.5) / log(2.0f)) / 10.0f;
	int integerPart = (int)mu % colorsNum;
	float fractPart = fmod(mu, 1.0f);

	const float3 bottomColor = colors[integerPart].xyz;
	const float3 topColor = colors[(integerPart + 1) % colorsNum].xyz;

	uchar3 color = convert_uchar3(mix(bottomColor, topColor, fractPart) * 255.0f);

	imageData[x + y * imageWidth] = (uchar4)(color.zyx, 0);
}

__kernel void celtic(
__global uchar4 *imageData,
__global float4 *colors,
double zoom,
double shiftX,
double shiftY,
int mouseX,
int mouseY,
int imageWidth,
int imageHeight,
int maxIteration,
int colorsNum) {

	int x = get_global_id(0);
	int y = get_global_id(1);
	if (x >= imageWidth || y >= imageHeight) {
		return;
	}

	double2 c = (double2)((2.0 * y / imageWidth - 1.0) / zoom + shiftY,
	(2.0 * x / imageHeight - 1.0) / zoom + shiftX);
	double2 z = (double2)(0.0);
	double2 zSquares = (double2)(0.0);
	int iteration = 0;

	while (zSquares.x + zSquares.y < 1000.0 && iteration < maxIteration) {
		iteration++;
		z.y = 2.0 * z.y * z.x;
		z.x = fabs(zSquares.x - zSquares.y);
		z += c.yx;
		zSquares = z * z;
	}
	float mu = ((float)iteration - log(log(zSquares.x + zSquares.y) * 0.5) / log(2.0f)) / 10.0f;
	int integerPart = (int)mu % colorsNum;
	float fractPart = fmod(mu, 1.0f);

	const float3 bottomColor = colors[integerPart].xyz;
	const float3 topColor = colors[(integerPart + 1) % colorsNum].xyz;

	uchar3 color = convert_uchar3(mix(bottomColor, topColor, fractPart) * 255.0f);

	imageData[x + y * imageWidth] = (uchar4)(color.zyx, 0);
}

__kernel void tricorn(
__global uchar4 *imageData,
__global float4 *colors,
double zoom,
double shiftX,
double shiftY,
int mouseX,
int mouseY,
int imageWidth,
int imageHeight,
int maxIteration,
int colorsNum) {

	int x = get_global_id(0);
	int y = get_global_id(1);
	if (x >= imageWidth || y >= imageHeight) {
		return;
	}

	double2 c = (double2)((2.0 * y / imageWidth - 1.0) / zoom + shiftY,
	(2.0 * x / imageHeight - 1.0) / zoom + shiftX);
	double2 z = (double2)(0.0);
	double2 zSquares = (double2)(0.0);
	int iteration = 0;

	while (zSquares.x + zSquares.y < 1000.0 && iteration < maxIteration) {
		iteration++;
		z.y = -2.0 * z.y * z.x;
		z.x = zSquares.x - zSquares.y;
		z += c.yx;
		zSquares = z * z;
	}
	float mu = ((float)iteration - log(log(zSquares.x + zSquares.y) * 0.5) / log(2.0f)) / 10.0f;
	int integerPart = (int)mu % colorsNum;
	float fractPart = fmod(mu, 1.0f);

	const float3 bottomColor = colors[integerPart].xyz;
	const float3 topColor = colors[(integerPart + 1) % colorsNum].xyz;

	uchar3 color = convert_uchar3(mix(bottomColor, topColor, fractPart) * 255.0f);

	imageData[x + y * imageWidth] = (uchar4)(color.zyx, 0);
}

__kernel void ship(
__global uchar4 *imageData,
__global float4 *colors,
double zoom,
double shiftX,
double shiftY,
int mouseX,
int mouseY,
int imageWidth,
int imageHeight,
int maxIteration,
int colorsNum) {

	int x = get_global_id(0);
	int y = get_global_id(1);
	if (x >= imageWidth || y >= imageHeight) {
		return;
	}

	double2 c = (double2)((2.0 * y / imageWidth - 1.0) / zoom + shiftY,
	(2.0 * x / imageHeight - 1.0) / zoom + shiftX);
	double2 z = (double2)(0.0);
	double2 zSquares = (double2)(0.0);
	int iteration = 0;

	while (zSquares.x + zSquares.y < 1000.0 && iteration < maxIteration) {
		iteration++;
		z.y = -2.0 * fabs(z.y * z.x);
		z.x = zSquares.x - zSquares.y;
		z += c.yx;
		zSquares = z * z;
	}
	float mu = ((float)iteration - log(log(zSquares.x + zSquares.y) * 0.5) / log(2.0f)) / 10.0f;
	int integerPart = (int)mu % colorsNum;
	float fractPart = fmod(mu, 1.0f);

	const float3 bottomColor = colors[integerPart].xyz;
	const float3 topColor = colors[(integerPart + 1) % colorsNum].xyz;

	uchar3 color = convert_uchar3(mix(bottomColor, topColor, fractPart) * 255.0f);

	imageData[x + y * imageWidth] = (uchar4)(color.zyx, 0);
}

__kernel void goose(
__global uchar4 *imageData,
__global float4 *colors,
double zoom,
double shiftX,
double shiftY,
int mouseX,
int mouseY,
int imageWidth,
int imageHeight,
int maxIteration,
int colorsNum) {

	int x = get_global_id(0);
	int y = get_global_id(1);
	if (x >= imageWidth || y >= imageHeight) {
		return;
	}

	double2 c = (double2)((1.0 - 2.0 * y / imageWidth) / zoom - shiftY,
						  (2.0 * x / imageHeight - 1.0) / zoom + shiftX);
	double2 z = (double2)(0.0);
	double2 zSquares = (double2)(0.0);
	int iteration = 0;

	while (zSquares.x + zSquares.y < 1000.0 && iteration < maxIteration) {
		iteration++;
		z.y = -2.0 * fabs(z.y) * z.x;
		z.x = zSquares.x - zSquares.y;
		z += c.yx;
		zSquares = z * z;
	}
	float mu = ((float)iteration - log(log(zSquares.x + zSquares.y) * 0.5) / log(2.0f)) / 10.0f;
	int integerPart = (int)mu % colorsNum;
	float fractPart = fmod(mu, 1.0f);

	const float3 bottomColor = colors[integerPart].xyz;
	const float3 topColor = colors[(integerPart + 1) % colorsNum].xyz;

	uchar3 color = convert_uchar3(mix(bottomColor, topColor, fractPart) * 255.0f);

	imageData[x + y * imageWidth] = (uchar4)(color.zyx, 0);
}

__kernel void heart(
__global uchar4 *imageData,
__global float4 *colors,
double zoom,
double shiftX,
double shiftY,
int mouseX,
int mouseY,
int imageWidth,
int imageHeight,
int maxIteration,
int colorsNum) {

	int x = get_global_id(0);
	int y = get_global_id(1);
	if (x >= imageWidth || y >= imageHeight) {
		return;
	}

	double2 c = (double2)((2.0 * y / imageWidth - 1.0) / zoom + shiftY,
	(2.0 * x / imageHeight - 1.0) / zoom + shiftX);
	double2 z = (double2)(0.0);
	double2 zSquares = (double2)(0.0);
	int iteration = 0;

	while (zSquares.x + zSquares.y < 1000.0 && iteration < maxIteration) {
		iteration++;
		z.y = 2.0 * z.y * fabs(z.x);
		z.x = zSquares.x - zSquares.y;
		z += c.yx;
		zSquares = z * z;
	}
	float mu = ((float)iteration - log(log(zSquares.x + zSquares.y) * 0.5) / log(2.0f)) / 10.0f;
	int integerPart = (int)mu % colorsNum;
	float fractPart = fmod(mu, 1.0f);

	const float3 bottomColor = colors[integerPart].xyz;
	const float3 topColor = colors[(integerPart + 1) % colorsNum].xyz;

	uchar3 color = convert_uchar3(mix(bottomColor, topColor, fractPart) * 255.0f);

	imageData[x + y * imageWidth] = (uchar4)(color.zyx, 0);
}

__kernel void julia(
	__global uchar4 *imageData,
	__global float4 *colors,
	double zoom,
	double shiftX,
	double shiftY,
	int mouseX,
	int mouseY,
	int imageWidth,
	int imageHeight,
	int maxIteration,
	int colorsNum) {

	int x = get_global_id(0);
	int y = get_global_id(1);
	if (x >= imageWidth || y >= imageHeight) {
		return;
	}

	double2 z = (double2)((2.0 * y / imageWidth - 1.0) / zoom + shiftY,
						(2.0 * x / imageHeight - 1.0) / zoom + shiftX);
	double2 c = (double2)(2.0 * mouseY / imageWidth - 1.0,
						2.0 * mouseX / imageHeight - 1.0);
	double2 zSquares = z * z;
	int iteration = 0;

	while (zSquares.x + zSquares.y < 4.0 && iteration < maxIteration) {
		iteration++;
		z.y = 2.0 * z.y * z.x;
		z.x = zSquares.x - zSquares.y;
		z += c.yx;
		zSquares = z * z;
	}
	float mu = ((float)iteration - log(log(zSquares.x + zSquares.y) * 0.5) / log(2.0f)) / 10.0f;
	int integerPart = (int)mu % colorsNum;
	float fractPart = fmod(mu, 1.0f);

	const float3 bottomColor = colors[integerPart].xyz;
	const float3 topColor = colors[(integerPart + 1) % colorsNum].xyz;

	uchar3 color = convert_uchar3(mix(bottomColor, topColor, fractPart) * 255.0f);

	imageData[x + y * imageWidth] = (uchar4)(color.zyx, 0);
}

__kernel void newton(
	__global uchar4 *imageData,
	__global float4 *dummy,
	double zoom,
	double shiftX,
	double shiftY,
	int mouseX,
	int mouseY,
	int imageWidth,
	int imageHeight,
	int maxIteration,
	int colorsNum) {

	int x = get_global_id(0);
	int y = get_global_id(1);
	if (x >= imageWidth || y >= imageHeight) {
		return;
	}

	const double threesqrt = 1.7320508076;
	double2 roots[3] = {
		{ -0.5, 0.5 * threesqrt },
		{ 1.0, 0.0 },
		{ -0.5, -0.5 * threesqrt }
	};

	float3 colors[] = {
		{0.89f, 0.15f, 0.07f},
		{0.18f, 1.0f, 0.17f},
		{0.19f, 0.1f, 0.91f}
	};

	double2 z = (double2)((2.0 * y / imageWidth - 1.0) / zoom + shiftY,
						  (2.0 * x / imageHeight - 1.0) / zoom + shiftX);

	float3 final_color = 0.0;
	int iteration = 0;
	bool runLoop = true;
	while (iteration < maxIteration && runLoop) {
		iteration++;
		double sum_sqr = dot(z, z);
		sum_sqr *= sum_sqr;
		double2 squares = z * z;

		double2 c;
		c.x = z.x - (squares.x - squares.y) / sum_sqr;
		c.y = z.y + 2.0 * z.x * z.y / sum_sqr;
		c /= 3.0;

		z -= c;

		for (int i = 0; i < 3; ++i) {
			double2 diff = z - roots[i];

			if (fabs(diff.x) < EPS && fabs(diff.y) < EPS) {
				final_color = colors[i];
				runLoop = false;
				break;
			}
		}
	}

	float coeff = (float)(maxIteration - iteration) / maxIteration;

	uchar3 color = convert_uchar3(final_color * (255.0f * coeff));

	imageData[x + y * imageWidth] = (uchar4)(color.zyx, 0);
}


