#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
char *stack,item,data;
float *stack1;
int top=0,top1=0;
float item1,data1;
void push(char );
void push1(float);
char pop();
float pop1();
float powe(float ,float );
void function();
void equation();
void conversion();
main()
{
	int a,l,g;
	stack=(char *)malloc(sizeof(char));//Stack for operators
	stack1=(float *)malloc(sizeof(float));//Stack for integers
	do
	{
		printf("---------------Choose your mode-----------------\n1-Arithmetic\n2-System of Equtation\n3-Conversion\n ");
		scanf("%d",&a);//For Chossing Modes
		switch(a)
		{
			case 1:
				do
				{
					function();
					printf("\nDo u want to continue means press 1 otherwise press 2\n");
					scanf("%d",&l);
				}while(l==1);
				break;
			case 2:
				do
				{
					equation();
					printf("\nDo u want to continue means press 1 otherwise press 2\n");
					scanf("%d",&l);
				}while(l==1);
				break;
			case 3:
				do
				{
					conversion();
					printf("\nDo u want to continue means press 1 otherwise press 2\n");
					scanf("%d",&l);
				}while(l==1);
				break;
		}
		printf("Do u want to EXIT means press 1 otherwise press 2\n");
		scanf("%d",&g);
	}while(g==2);
}
			void function()
			{
				printf("\t1\t2\t3\t4\n\t5\t6\t7\t8\n\t9\t0\t+\t-\n\t*\t/\t[\t]\n\t(\t)\t\n");
				char *s;
				char d;
				float y=0.0;
				int t,i;
				float w,q,result,RESULT=0.0;
				s=(char *)malloc(sizeof(char));
				printf("Enter your Equation\nExample:(12+34*45/65)\n");
				scanf("%s",s);
				t=strlen(s);
				for(i=0;i<t;i++)
				{
					if(*(s+i)=='('||*(s+i)=='[')
					{
						push(*(s+i));
							if(*(s+i+1)=='-')
							push1(0.0);
					}
					else if(*(s+i)=='-')
					{
						if(y!=0.0)
							push1(y);
						y=0.0;
						while(stack[top]=='*'||stack[top]=='/'||stack[top]=='+'||stack[top]=='-'||stack[top]=='^')
						{
							d=pop();//poping operator
							q=pop1();//poping integer from top of the stack
							w=pop1();//poping second integer for process
							switch(d)
							{
								case '+':
									result=w+q;
									break;
								case '-':
									result=w-q;
									break;
								case '*':
									result=w*q;
									break;
								case '/':
									result=w/q;
									break;
								case '^':
									result=powe(w,q);
									break;
							}
							push1(result);
						}
						push(*(s+i));
					}
					else if(*(s+i)=='+')
					{
						if(y!=0.0)
							push1(y);
						y=0.0;

						while(stack[top]=='*'||stack[top]=='/'||stack[top]=='^'||stack[top]=='+'||stack[top]=='-')
						{
							d=pop();//poping operator
							q=pop1();//poping integer from top of the stack
							w=pop1();//poping second integer for process
							switch(d)
							{
								case '+':
									result=w+q;
									break;
								case '-':
									result=w-q;
									break;
								case '*':
									result=w*q;
									break;
								case '/':
									result=w/q;
									break;
								case '^':
									result=powe(w,q);
									break;
							}
							push1(result);
						}
						push(*(s+i));
					}
					else if(*(s+i)=='*')
                                        {
						if(y!=0.0)
							push1(y);
						y=0.0;
						while(stack[top]=='^'||stack[top]=='/'||stack[top]=='*')
                                                {
                                                        d=pop();//poping operator
                                                        q=pop1();//poping integer from top of the stack
                                                        w=pop1();//poping second integer for process
                                                        switch(d)
                                                        {
                                                                case '*':
                                                                        result=w*q;
                                                                        break;
                                                                case '/':
                                                                        result=w/q;
                                                                        break;
								case '^':
									result=powe(w,q);
									break;
                                                        }
                                                        push1(result);
                                                }
                                                push(*(s+i));
					}
					else if(*(s+i)=='/')
                                        {
						if(y!=0.0)
							push1(y);

						y=0.0;

                                                while(stack[top]=='^'||stack[top]=='/')
                                                {
                                                        d=pop();//poping operator
                                                        q=pop1();//poping integer from top of the stack
                                                        w=pop1();//poping second integer for process
                                                        switch(d)
                                                        {
								case '/':
									result=(w/q);
									break;
                                                                case '^':
									result=powe(w,q);
									break;
                                                        }
                                                        push1(result);
                                                }
                                                push(*(s+i));
					}
					else if(*(s+i)=='^')
					{
						if(y!=0.0)
							push1(y);
						y=0.0;
						push(*(s+i));
					}
					else if(*(s+i)==')'||*(s+i)==']')
					{
						if(y!=0)
							push1(y);
						y=0.0;
						while(stack[top]=='+'||stack[top]=='-'||stack[top]=='*'||stack[top]=='/'||stack[top]=='^')
						{
					                d=pop();//poping operator
							q=pop1();//poping integer from top of the stack
                                                        w=pop1();//poping second integer for process

                                                        switch(d)
                                                        {
                                                                case '+':
                                                                        result=w+q;
                                                                        break;
                                                                case '-':
                                                                        result=w-q;
                                                                        break;
                                                                case '*':
                                                                        result=w*q;
                                                                        break;
                                                                case '/':
                                                                        result=w/q;
                                                                        break;
								case '^':
									result=powe(w,q);
									break;
                                                        }
                                                        push1(result);
					    	}
					pop();
					}
		  			else
					{
						y=(y*10.0)+(s[i]-'0');
					}
				}

				RESULT=pop1();
				printf("\nRESULT=%f\n",RESULT);
			}
               			void push(char item)
                                {
                                        top++;
                                        stack[top]=item;
			        }
                                void push1(float item1)
                                {
                                        top1++;
                                        stack1[top1]=item1;
			        }
                                char pop()
                                {

                                        if(top==0)
                                                printf("Stack is underflow\n");
                                        else
                                        {
                                                data=stack[top];
                                                top--;
						return(data);
                                        }
                                }
                                float pop1()
                                {
                                        if(top1==0)
                                                printf("Stack is underflow\n");
                                        else
                                        {
                                                data1=stack1[top1];
                                                top1--;
						return(data1);
                                        }
                                }
				float powe(float a,float b)
				{
					float i,c=1;
					for(i=0;i<b;i++)
						c=c*a;
					return(c);
				}










void equation()
{
	float a,b,c,d,e,f;
	float x,y,root1,root2;
	int choice;
	printf("enter your choice\n 1.quadratic equation 2.roots of equation\n");
	scanf("%d",&choice);
	switch(choice)
		{
			case 1:
				printf("enter the equation\n  ex: ax+by+c=0\t\n      dx+ey+f=0\n");
				scanf("%f%f%f%f%f%f",&a,&b,&c,&d,&e,&f);
				x=((f*b)-(c*e))/((a*e)-(d*b));
	                        y=((c*d)-(f*a))/((a*e)-(d*b));
				printf("result is: %f  %f\n",x,y);
				break;

			case 2:
				printf("enter values\n");
				scanf("%f%f%f",&a,&b,&c);
				printf("%f+sqrt(%f)\n",((-b)/(2*a)),((b*b-4*a*c)/((2*a)*(2*a))));
				printf("%f-sqrt(%f)\n",((-b)/(2*a)),((b*b-4*a*c)/((2*a)*(2*a))));
				break;

			default:
				printf("unable to understand your choice\n");
		}
}




void conversion()
{
int n;
int dec_bin(int);
void dec_hex(int);
int dec_oct(int);
int bin_dec(int);
void bin_hex(int);
int bin_oct(int);
int hex_dec();
int hex_bin();
int hex_oct();
int oct_dec(int);
int oct_bin(int);
void oct_hex(int);
int choice,y;
printf("Enter your choice:\n");
printf("choice\n\t1.dec_bin\t2.dec_hex\t3.dec_oct\n\t4.bin_dec\t5.bin_hex\t6.bin_oct\n\t7.hex_dec\t8.hex_bin\t9.hex_oct\n\t10.oct_dec\t11.oct_bin\t");
printf("12.oct_hex\n");
scanf("%d",&choice);
switch(choice)
{
	case 1:
		printf("enter the value for n\n");
		scanf("%d",&n);
		y=dec_bin(n);
		printf("The binary value is: %d\n",y);
		  break;
	case 2:
		printf("enter the value for n\n");
		scanf("%d",&n);
		 dec_hex(n);
		  break;
	case 3:
		printf("enter the value for n\n");
		scanf("%d",&n);
		y= dec_oct(n);
		printf("The octal value is: %d",y);
		 break;
	case 4:
		printf("enter the value for n\n");
		scanf("%d",&n);
		y= bin_dec(n);
		printf("The decimal value is: %d",y);
		break;
	case 5:
		printf("enter the value for n\n");
		scanf("%d",&n);
		bin_hex(n);
		break;
	case 6:
		printf("enter the value for n\n");
		scanf("%d",&n);
		y=bin_oct(n);
		printf("The octal value is: %d",y);
		break;
	case 7:
		y=hex_dec();
		printf("The decimal value is: %d",y);
		break;
	case 8:
		y=hex_bin();
		printf("The binary value is: %d",y);
		break;
	case 9:
		y=hex_oct();
		printf("The Octal value is: %d",y);
		break;
	case 10:
		printf("enter the value for n\n");
		scanf("%d",&n);
		y=oct_dec(n);
		printf("The Decimal value is: %d",y);
		break;
	case 11:
		printf("enter the value for n\n");
		scanf("%d",&n);
		y=oct_bin(n);
		printf("The Binary value is: %d",y);
		break;

	case 12:
		printf("enter the value for n\n");
		scanf("%d",&n);
		oct_hex(n);
		break;
	default:
		printf("Wrong Choices");
		break;
}
}
int dec_bin(int x)
{
	int b=0,pcs=1,r;
	while(x>0)
	{
		r=x%2;
		b=b+r*pcs;
		pcs=pcs*10;
		x=x/2;
	}
return (b);
}

void dec_hex(int x)
{
	int q,i,j;
	int y[10];
	for(j=0;x>0;j++)
	{
		q=x%16;
		y[j]=q;
		x=x/16;
	}
printf("The hexa value is :");
for(i=j-1;i>=0;i--)
{
	if(y[i]==10)
	printf("a");
	else if(y[i]==11)
	printf("b");
	else if(y[i]==12)
        printf("c");
	else if(y[i]==13)
        printf("d");
	else if(y[i]==14)
        printf("e");
	else if(y[i]==15)
        printf("f");
        else
	printf("%d",y[i]);
}

}
int dec_oct(int x)
{
	int s=0,p=1;
	while(x>0)
	{
		s=s+(x%8)*p;
		p=p*10;
		x=x/8;
	}
return(s);
}
int bin_dec(int x)
{
	int b,pos=1,sum=0;
	while(x>0)
	{
		b=x%10;
		sum=sum+(pos*b);
		pos=pos*2;
		x=x/10;
	}
return (sum);
}

int oct_dec(int x)
{
	int d=0,pos=1,r;
	while(x>0)
	{
		r=x%10;
		if(r==8||r==9)
		{
			printf("Syntax Errorty");
			break;
		}
		else
		{
			d=d+r*pos;
			pos=pos*8;
			x=x/10;
		}
	}
return(d);
}
int hex_dec()
{
	char q[20];
	int d=0,pos=1,y,ans,i;
	printf("enter the num hexadecimal number \n");
	scanf("%s",q);
	y=strlen(q);
	for(i=y-1;i>=0;i--)
	{
		if(q[i]=='a')
        	{
		ans=10;
		d=d+(ans*pos);
		}
        	else if(q[i]=='b')
        	{
		ans=11;
		d=d+(ans*pos);
		}
		else if(q[i]=='c')
                {
		ans=12;
                d=d+(ans*pos);
		}
		else if(q[i]=='d')
                {
		ans=13;
                d=d+(ans*pos);
		}
		else if(q[i]=='e')
                {
		ans=14;
                d=d+(ans*pos);
		}
		else if(q[i]=='f')
                {
		ans=15;
                d=d+(ans*pos);
		}
		else
		{
		ans=(q[i]-'0');
		d=d+(ans*pos);
		}
	pos=pos*16;
	}

return(d);
}
void bin_hex(int x)
{
	int i;
	i=bin_dec(x);
	dec_hex(i);
}
int bin_oct(int x)
{
	int i,j;
	i=bin_dec(x);
	j=dec_oct(i);
	return(j);
}
int hex_bin()
{
	int i,j;
	i=hex_dec();
	j=dec_bin(i);
	return(j);
}
int hex_oct()
{
	int i,j;
	i=hex_dec();
	j=dec_oct(i);
	return(j);
}
int oct_bin(int x)
{
	int i,j;
	i=oct_dec(x);
	j=dec_bin(i);
	return(j);
}

void oct_hex(int x)
{
	int i;
	i=oct_dec(x);
	dec_hex(i);
}
