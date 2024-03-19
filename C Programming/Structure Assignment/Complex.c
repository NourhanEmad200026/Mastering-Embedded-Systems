v/*
 * ass1q2.c
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */
#include <stdio.h>
#include <string.h>
struct SComplex{
	float m_R;
	float m_I;
};
struct SComplex Addcomplex(struct SComplex A,struct SComplex B)
{
	struct SComplex R;
	R.m_R=A.m_R+B.m_R;
	R.m_I=A.m_I+B.m_I;
	return R;
}
struct SComplex ReadComplex(char name[])
{
	struct SComplex C;
	printf("Enter %s complex value: ",name);
	fflush(stdout);
	scanf("%f %f",&C.m_R,&C.m_I);
	return C;
}
void printComplex(char name[],struct SComplex C)
{
	printf("%s=(%lf)+(%lf)j",name,C.m_R,C.m_I);
}
int main(){
	struct SComplex X,Y,Z;
	X=ReadComplex("X");
	Y=ReadComplex("Y");
	Z=Addcomplex(X,Y);
	printComplex("Z",Z);
}
