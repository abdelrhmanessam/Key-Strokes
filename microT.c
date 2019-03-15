#include <REG52.H>
#include <stdio.h>
#include <math.h>
long* train(void);
void test (long* a , long* b);
void timer0_isr(void);
long* p1;
long* p2;
unsigned long intervals[10] = {0};
static long u_i = 0;
char key[11] = {'.','t','i','e','5','R','o','n','a','l','\0'};
sbit users = P0^0;
sbit phase = P0^1;
sbit LED1 = P0^2;
sbit LED2 = P0^3;
void timer0_isr(void) interrupt 3 {
	u_i++;
}

void main (void){
SCON = 0x50;
TMOD |= 0x20;
TH1 = 0x00;
TL1 = TH1;
TI = 1;
ET1 = 1;
EA = 1;
LED1 = 0;
LED2 = 0;
while(1)
{
if (phase == 1)
{
if (users == 0)
{
p1 = train();
} 
else 
{
p2 = train();
}
}
else
{
test(p1, p2);
}
}
}

long* train(void){
int j;
int i = 0;
int k = 0;
char x;
int count = 0;
while(count < 5){
u_i = 0;
TR1 = 1;
TL1 = TH1;
x = _getkey();
if (x == key[i]) {
intervals[i] = intervals[i] + u_i;
i++;
}
else{
count = 0;
i = 0;
for( j = 0; j < 10; j++)
{
intervals[j] = 0;
}
}
if (i == 10) {
count++;
i = 0;
}
}
for (k = 0; k < 10; k++){
intervals[k] = intervals[k]/5;
}
return intervals;
}

void test (long* a , long* b)
{
char j;
long sum1 = 0;
long sum2 = 0;
long temp1;
long temp2;
char i = 0;
char x;
while(i<10){
u_i = 0;
TR1 = 1;
TL1 = TH1;
x = _getkey();
if (x == key[i]) {
intervals[i] = u_i;
i++;
} else {
i = 0;
}
}
for ( j = 0; j < 10; j++ )
{
temp1 = (intervals[j] - *(a+j)) * (intervals[j] - *(a+j));
temp2 = (intervals[j] - *(b+j)) * (intervals[j] - *(b+j));
sum1 = sum1 + temp1;
sum2 = sum2 + temp2;
}
if (sum1 < sum2)
{
LED1 = 1;
}
else
{
LED2 = 1;
}
}
