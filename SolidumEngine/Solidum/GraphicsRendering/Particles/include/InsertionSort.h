#pragma once
#include "../../../sysInclude.h"

#include "Particle.h"

class InsertionSort
{
public:
	InsertionSort();
	~InsertionSort();

	void insertionSort(std::vector<Particle*>* arr) {

		int i, j;

		Particle* tmp;

		for (i = 1; i < arr->size(); i++) {

			j = i;

			while (j > 0 && arr[j - 1] > arr[j]) {

				tmp = arr->operator[](j);

				arr[j] = arr[j - 1];

				arr->operator[](j - 1) = tmp;

				j--;

			}

		}

	}
};

