#include <iostream>
#include <fstream>
using namespace std;

struct pixel
{
	int red;
	int green;
	int blue;
};

struct image
{
	int width, height;
	pixel** pixel_array;
};

image readImageFromFile(char* file_name)
{
	ifstream in_file(file_name);
	if (!in_file.is_open())
	{
		return { 0, 0, NULL };
	}

	char temp[3] = { 0 };
	in_file.getline(temp, 3);

	int width, height;

	in_file >> width >> height;

	int rgb_logical_divider;

	in_file >> rgb_logical_divider;

	pixel** pixel_array = new pixel * [height];

	int logical_red, logical_green, logical_blue;

	for (int i = 0; i < height; ++i) {
		pixel_array[i] = new pixel[width];

		for (int j = 0; j < width; ++j)
		{
			in_file >> logical_red >> logical_green >> logical_blue;

			pixel_array[i][j].red = logical_red * 255 / rgb_logical_divider;
			(*(*(pixel_array + i) + j)).green = logical_green * 255 / rgb_logical_divider;
			(*(pixel_array + i) + j)->blue = logical_blue * 255 / rgb_logical_divider;
		}
	}

	in_file.close();
	return { width, height, pixel_array };
}

void writeImageToFile(char* file_name, image photo)
{
	ofstream out_file(file_name);
	if (!out_file.is_open())
	{
		return;
	}

	out_file << "P3\n";

	out_file << photo.width << ' ' << photo.height << '\n';

	out_file << "255\n";

	for (int i = 0; i < photo.height; ++i) {
		for (int j = 0; j < photo.width; ++j)
		{
			out_file << photo.pixel_array[i][j].red << ' ';
			out_file << photo.pixel_array[i][j].green << ' ';
			out_file << photo.pixel_array[i][j].blue << ' ';
		}
		out_file << endl;
	}

	out_file.close();
}

void deleteImage(image& photo)
{
	if (photo.pixel_array != NULL)
	{
		for (int i = 0; i < photo.height; ++i)
		{
			delete[] photo.pixel_array[i];
		}
		delete[] photo.pixel_array;
	}
	photo.pixel_array = NULL;
	photo.width = 0;
	photo.height = 0;
}

void negatives(image photo)
{
	if (photo.pixel_array != NULL)
	{
		for (int i = 0; i < photo.height; ++i)
		{
			for (int j = 0; j < photo.width; ++j)
			{
				photo.pixel_array[i][j].red = 255 - photo.pixel_array[i][j].red;
				photo.pixel_array[i][j].blue = 255 - photo.pixel_array[i][j].blue;
				photo.pixel_array[i][j].green = 255 - photo.pixel_array[i][j].green;
			}
		}
	}
}

int main()
{
	char rav_grauss[] = "C:\\Users\\Raphael\\Desktop\\tirgul-mavo-files\\profile.ppm";
	char rav_grauss1[] = "C:\\Users\\Raphael\\Desktop\\profile1.ppm";

	image rav = readImageFromFile(rav_grauss);
	negatives(rav);
	writeImageToFile(rav_grauss1, rav);

	deleteImage(rav);

	return 0;
}