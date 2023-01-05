#include <stdio.h>

double bmi_calculate(double h, double w);

int main(){
	double height, weight, bmi;
	printf("BMI 계산 프로그램\n");
	printf("입력");
	scanf("%lf %lf", &height, &weight);
	bmi = bmi_calculate(height, weight);
	printf("bmi: %lf", bmi);
	return 0;
}

double bmi_calculate(double h, double w){
	double BMI;
	BMI = w / (h * h);
	return BMI;
}