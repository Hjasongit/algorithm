/*****************************************
* Program Assignment:쳲����������㷨�Ż�
* Author:���ɷ�
* Date:2017/8/2
*****************************************/

#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdint.h>
#include<float.h>

//#define NDEBUG

/* �ݹ��㷨ʵ�� */
uint64_t fibonacci1(unsigned int n) {
	if (n == 0) return 0;
	if (n <= 2) return 1;
	return fibonacci1(n - 1) + fibonacci1(n - 2);
}
/* ѭ�������㷨ʵ�� */
uint64_t fibonacci2(unsigned int n) {
	if (n == 0) return 0;
	if (n == 1 || n == 2) return 1;
	uint64_t f1 = 1, f2 = 1, fn;
	for (unsigned int i = 3; i <= n; i++) {
		fn = f1 + f2;
		f1 = f2;
		f2 = fn;
	}
	return fn;
}
/* ԭʼ�����㷨ʵ�� */
uint64_t fibonacci3(unsigned int n) {
	uint64_t m[2][2] = { 1,1,1,0 }; // 1�ξ���
	uint64_t result[][2] = { 1,0,0,1 }; // ��λ����
	uint64_t temp[2][2];
	// ����n�ξ���
	for (unsigned int i = 1; i <= n; i++) {
		temp[0][0] = result[0][0] * m[0][0] + result[0][1] * m[1][0];
		temp[0][1] = result[0][0] * m[0][1] + result[0][1] * m[1][1];
		temp[1][0] = result[1][0] * m[0][0] + result[1][1] * m[1][0];
		temp[1][1] = result[1][0] * m[0][1] + result[1][1] * m[1][1];
		memcpy(result, temp, sizeof(uint64_t) * 4);
	}
	// result[1][0] * 1 + result[1][1] * 0;
	return result[1][0] * 1;
}
/* ����������Ż��㷨 */
uint64_t fibonacci4(unsigned int n) {
	uint64_t m[2][2] = { 1,1,1,0 }; // 1�ξ���
	uint64_t result[][2] = { 1,0,0,1 }; // ��λ����
	uint64_t temp[2][2];
	while (n) {
		if (n & 1) {
			temp[0][0] = result[0][0] * m[0][0] + result[0][1] * m[1][0];
			temp[0][1] = result[0][0] * m[0][1] + result[0][1] * m[1][1];
			temp[1][0] = result[1][0] * m[0][0] + result[1][1] * m[1][0];
			temp[1][1] = result[1][0] * m[0][1] + result[1][1] * m[1][1];
			memcpy(result, temp, sizeof(uint64_t) * 4);
		}
		// 2��4��8...���ݾ���
		temp[0][0] = m[0][0] * m[0][0] + m[0][1] * m[1][0];
		temp[0][1] = m[0][0] * m[0][1] + m[0][1] * m[1][1];
		temp[1][0] = m[1][0] * m[0][0] + m[1][1] * m[1][0];
		temp[1][1] = m[1][0] * m[0][1] + m[1][1] * m[1][1];
		memcpy(m, temp, sizeof(uint64_t) * 4);
		n >>= 1;
	}
	// result[1][0] * 1 + result[1][1] * 0;
	return result[1][0] * 1;
}

/* ��������ݲ���㷨 */
uint64_t fibonacci5(unsigned int n) {
	const static uint64_t cache[][2][2] = {
		{ 1, 0, 0, 1 },// 0����(����)
		{ 1, 1, 1, 0 },// 1����(2^0,1)
		{ 2, 1, 1, 1 },// 2����(2^1,2)
		{ 5, 3, 3, 2 },// 4����(2^2,3)
		{ 34, 21 ,21, 13 },// 8����(2^3,4)
		{ 1597, 987, 987 ,610 },// 16����(2^4,5)
		{ 3524578, 2178309, 2178309, 1346269 },// 32����(2^5,4)
		{ 17167680177565, 10610209857723, 10610209857723, 6557470319842 },//64����(2^6,5)
		{ 8102862946581596898, 18154666814248790725, 18154666814248790725, 8394940206042357789 }//128����(2^7,6)
	};
	uint64_t result[][2] = { 1, 0, 0, 1 }; // ��λ����
	uint64_t temp[2][2];
	int bit_pos = 1;
	while (n) {
		if (n & 1) {
			temp[0][0] = result[0][0] * cache[bit_pos][0][0] + result[0][1] * cache[bit_pos][1][0];
			temp[0][1] = result[0][0] * cache[bit_pos][0][1] + result[0][1] * cache[bit_pos][1][1];
			temp[1][0] = result[1][0] * cache[bit_pos][0][0] + result[1][1] * cache[bit_pos][1][0];
			temp[1][1] = result[1][0] * cache[bit_pos][0][1] + result[1][1] * cache[bit_pos][1][1];
			memcpy(result, temp, sizeof(uint64_t) * 4);
		}
		n >>= 1;
		bit_pos++;
	}
	// result[1][0] * 1 + result[1][1] * 0;
	return result[1][0] * 1;
}

/* ͨ�ʽֱ����� */
uint64_t fibonacci6(unsigned int n) {
	const double sqrt5 = 2.2360679774997896964091736687313;
	const double a = (sqrt5 + 1) / 2;
	const double b = (1 - sqrt5) / 2;
	const double sqrt1_5 = 1 / sqrt5;

	return (uint64_t)((pow(a, n) - pow(b, n))*sqrt1_5);
}

/* ����ʱ���� */
double duration(struct timespec *end, struct timespec *start) {
	double d_sec = difftime(end->tv_sec, start->tv_sec);
	long d_nsec = end->tv_nsec - start->tv_nsec;
	return (d_sec*10e9 + d_nsec);
}

/* �㷨���� */
void compare_and_test() {
	typedef uint64_t(*PFUNC)(unsigned int n);
	PFUNC pFuncs[] = { fibonacci2 ,fibonacci3, fibonacci4, fibonacci5, fibonacci6 };
	struct timespec start, end;
	for (int j = 0; j < sizeof(pFuncs) / sizeof(PFUNC); j++) {
		timespec_get(&start, TIME_UTC);
		// 93���ᷢ�������������Լ���ʱ�䣬�������������
		for (int i = 0; i < 95; i++) {
#			ifdef NDEBUG
			(*pFuncs[j])(i);
#			else
			printf("%llu ", (*pFuncs[j])(i));
#			endif
		}
		timespec_get(&end, TIME_UTC);
		printf("\t duration: %lf nanosecond\n", duration(&end, &start));
	}
}

void power_matrix(uint64_t m[][2], unsigned int exp) {
	uint64_t result[][2] = { 1,0,0,1 }; // ��λ����
	uint64_t temp[2][2];
	// ����n�ξ���
	for (unsigned int i = 1; i <= exp; i++) {
		temp[0][0] = result[0][0] * m[0][0] + result[0][1] * m[1][0];
		temp[0][1] = result[0][0] * m[0][1] + result[0][1] * m[1][1];
		temp[1][0] = result[1][0] * m[0][0] + result[1][1] * m[1][0];
		temp[1][1] = result[1][0] * m[0][1] + result[1][1] * m[1][1];
		memcpy(result, temp, sizeof(uint64_t) * 4);
	}
	memcpy(m, result, sizeof(uint64_t) * 4);
}
void generate_matrix() {
	uint64_t m[2][2] = { 1,1,1,0 }; // 1�ξ���
	uint64_t temp[2][2];
	for (int i = 0; i < 8; i++) {
		memcpy(temp, m, 4 * sizeof(uint64_t));
		printf("{");
		power_matrix(temp, 1 << i);
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				printf("%llu, ", temp[j][k]);
			}
		}
		printf("},\n");
	}
}

/* �����˷���ʵ��(ʹ�üӷ�����λ����) */
int quick_multi(int a, int b) {
	int bits, factor;
	if (a < b) {
		bits = a;
		factor = b;
	}
	else {
		bits = b;
		factor = a;
	}

	int result = 0;
	while (bits) {
		if (bits & 1)
			result += factor;
		bits >>= 1; // ��2
		factor <<= 1; // ��2
	}
	return result;
}

/* �������������� */
int quick_pow(int base, int exp) {
	int result = 1;
	while (exp) {
		if (exp & 1)
			result *= base;
		exp >>= 1;
		base <<= 1; // 2,4,8...����
	}
	return result;
}

void main() {
	compare_and_test();
	//generate_matrix();
}