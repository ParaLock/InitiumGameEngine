#pragma once
#include "../../../sysInclude.h"

#include "Particle.h"

struct RenderPassPacket_ParticleEmitterData;

class InsertionSort
{
public:
	InsertionSort();
	~InsertionSort();

	void particleSelectionSort(std::vector<Particle*>* arr) {

		if (arr->size() == 0)
			return;

		if (arr->size() == 2) {
			if (arr->at(0)->_distance < arr->at(1)->_distance) {
				std::swap(arr->at(0), arr->at(1));
			}

			return;
		}

		int i = 0;

		int j = i + 1;

		while (i < arr->size() - 1) {
			
			while (j < arr->size() - 1) {
				if (arr->at(j)->_distance > arr->at(i)->_distance) {

					std::swap(arr->at(i), arr->at(j));
				}
				j++;
			}
			i++;
			j = i + 1;

		}
	}

	bool particleBatchSelectionSort(std::vector<std::tuple<std::shared_ptr<ParticleBatch>, RenderPassPacket_ParticleEmitterData*>>* arr) {

		if (arr->size() == 0)
			return false;

		if (arr->size() == 2) {

			if (std::get<0>(arr->at(0))->_particlesToRender->front()->_distance < std::get<0>(arr->at(1))->_particlesToRender->front()->_distance) {
				std::swap(arr->at(0), arr->at(1));
			}

			return true;
		}

		int i = 0;

		int j = i + 1;

		while (i < arr->size() - 1) {

			while (j < arr->size() - 1) {
				if (std::get<0>(arr->at(j))->_particlesToRender->front()->_distance > std::get<0>(arr->at(i))->_particlesToRender->front()->_distance) {

					std::swap(arr->at(i), arr->at(j));
				}
				j++;
			}
			i++;
			j = i + 1;

		}

		return true;
	}
};

