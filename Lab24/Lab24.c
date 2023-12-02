#include <stdio.h>
#include <Windows.h>

int /*double*/ factorial(int fact){ //до 31 с int нормально       /отрицательное - ошибка
	if (fact == 0) {
		return 1;
	}
	return factorial(fact - 1) * fact;
}

void task2_1(int x) {
	printf("%d ", x);
	if (x > 1) {
		return task2_1(x - 2);
	}
	printf("\n2_1 завершено\n");
}
void task2_2(int x) {
	if (x > 1) {
		task2_2(x - 2);
	}
	printf("%d ", x);
}
void task2_3(int x) {
	printf("%d ", x);
	if (x > 1) {
		task2_3(x - 2);
	}
	printf("%d ", x);
}
void recEGE1(int n) {
	if (n >= 1) {
		printf(" %d", n);
		recEGE1(n - 1);
		recEGE1(n - 1);
	}
}
void F1(int n) {
	if (n > 2) {
		printf("%d \n", n);
		F1(n - 3);
		F1(n - 4);
	}
}
void F2(int n) {
	printf("%d \n", n);
	if (n < 5) {
		F2(n + 1);
		F2(n + 3);
	}
}
void G3(int n);
void F3(int n) {
	if (n > 0) {
		G3(n - 1);
	}
}
void G3(int n) {
	printf("*");
	if (n > 1){
		F3(n - 3);
	}
}
void main() { 
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int fact = 5;
	
	int num;
	do {
		printf("\n0 - факториал\n");
		printf("1 - последовательности чисел\n");
		printf("2 - recEGE1\n");
		printf("3 - F1\n");
		printf("4 - F2\n");
		printf("5 - F3\n");
		scanf_s("%d", &num);
		switch (num)
		{
		case 0:
			printf("%d! = %d ", fact, factorial(fact));
			break;
		case 1:
			task2_1(11);
			task2_2(11);
			printf("\n2_2 завершено\n");
			task2_3(3);
			printf("\n2_3 завершено\n");
			break;
		case 2:
			//для трассировки в VS 
			recEGE1(3);
			break;
		case 3:
			F1(10);
			break;
		case 4:
			F2(1);
			break;
		case 5:
			F3(13);
			break;

		}
	} while (1);
}
//long fuct2(int n) {
//	if (n == 0) {
//		return 1;
//	}
//
//	long res = fuct2(n - 1) * n;
//	return res;
//}
//
//void main() {
//	int n = 5;
//	long f = fuct2(n);
//
//	printf("%d! = %ld", n, f);
//}

