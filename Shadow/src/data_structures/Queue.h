#pragma once

#include "../core/Core.h"

namespace ShadowEngine {
	namespace DataStructures {

		template<typename T>
		struct SHADOW_API Node { // ADD RULE OF 3// CHANGE TO CLASS SEE IF THAT HELPS????

		public:
			Node<T>* next;
			T data;

		};

		template<typename T>
		class SHADOW_API Queue {
		public:


			void Enqueue(T data) {

				Node<T>* temp = new Node<T>;
				temp->data = data;
				temp->next = nullptr;

				if (front == nullptr)
					front = rear = temp;
				else
				{
					rear->next = temp;
					rear = temp;
				}

				size++;

			}

			void Dequeue() {

				Node<T>* temp;

				if (front == nullptr) {

					return;
				}
				else
				{
					temp = front;
					front = front->next;


					size--;
					delete temp->data;
					delete temp;
				}

			}


			bool Empty() {
				return size == 0;
			}

			Node<T>* Peek() {
				if (front == nullptr)
					return nullptr;
				return front;
			}

			~Queue() { delete front; }
		private:
			Node<T>* front = nullptr;
			Node<T>* rear = nullptr;
			int size = 0;


		};

	}
}
