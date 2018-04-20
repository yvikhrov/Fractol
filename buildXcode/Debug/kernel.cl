#define EPS 1e-4f

__kernel void mandelbrot(
	__global uchar4 *imageData,
	__global float4 *colors,
	float zoom,
	float shiftX,
	float shiftY,
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

	float2 c = (float2)((2.0f * y / imageWidth - 1.0f) / zoom + shiftY,
						(2.0f * x / imageHeight - 1.0f) / zoom + shiftX);
	float2 z = (float2)(0.0f);
	float2 zSquares = (float2)(0.0f);
	int iteration = 0;

	while (zSquares.x + zSquares.y < 1000.0f && iteration < maxIteration) {
		iteration++;
		z.y = 2.0f * z.y * z.x;
		z.x = zSquares.x - zSquares.y;
		z += c.yx;
		zSquares = z * z;
	}
	float mu = ((float)iteration - log(log(zSquares.x + zSquares.y) * 0.5f) / log(2.0f)) / 10.0f;
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
	float zoom,
	float shiftX,
	float shiftY,
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

	float2 z = (float2)((2.0f * y / imageWidth - 1.0f) / zoom + shiftY,
						(2.0f * x / imageHeight - 1.0f) / zoom + shiftX);
	float2 c = (float2)(2.0f * mouseY / imageWidth - 1.0f,
						2.0f * mouseX / imageHeight - 1.0f);
	float2 zSquares = z * z;
	int iteration = 0;

	while (zSquares.x + zSquares.y < 4.0f && iteration < maxIteration) {
		iteration++;
		z.y = 2.0f * z.y * z.x;
		z.x = zSquares.x - zSquares.y;
		z += c.yx;
		zSquares = z * z;
	}
	float mu = ((float)iteration - log(log(zSquares.x + zSquares.y) * 0.5f) / log(2.0f)) / 10.0f;
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
	float zoom,
	float shiftX,
	float shiftY,
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

	const float threesqrt = 1.732051f;
	float2 roots[3] = {
		{ -0.5f, 0.5f * threesqrt },
		{ 1.0f, 0.0f },
		{ -0.5f, -0.5f * threesqrt }
	};

	float3 colors[] = {
		{0.89f, 0.15f, 0.07f},
		{0.18f, 1.0f, 0.17f},
		{0.19f, 0.1f, 0.91f}
	};

	float2 z = (float2)((2.0f * y / imageWidth - 1.0f) / zoom + shiftY,
						(2.0f * x / imageHeight - 1.0f) / zoom + shiftX);

	float3 final_color = 0.0f;
	int iteration = 0;
	bool runLoop = true;
	while (iteration < maxIteration && runLoop) {
		iteration++;
		float sum_sqr = dot(z, z);
		sum_sqr *= sum_sqr;
		float2 squares = z * z;

		float2 c;
		c.x = z.x - (squares.x - squares.y) / sum_sqr;
		c.y = z.y + 2.0f * z.x * z.y / sum_sqr;
		c /= 3.0f;

		z -= c;

		for (int i = 0; i < 3; ++i) {
			float2 diff = z - roots[i];

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


