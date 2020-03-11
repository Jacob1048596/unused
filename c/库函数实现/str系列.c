#include<stdio.h>
#include <assert.h>
#include <string.h>
int Strlen(const char* str)
{
  assert(str!=NULL);
  int ret =0;
  while (*str!='\0') {
    /* code */
    ret++;
    str++;
  }
  return ret;
}
char* Strcpy(char* destination, const char* source)
{
   assert(destination!=NULL&&source!=NULL);
  char* ret=destination;
   if(strlen(destination)<strlen(source)) return NULL;
   while (*destination!='\0'&&*source!='\0') {
     /* code */
     *destination=*source;
     destination++;
     source++;
   }
   *destination='\0';
   return ret;
 }
char* Strcat(char* destination,const char* source)
{
   assert(destination!=NULL&&source!=NULL);
   char* ret=destination;
  if(strlen(destination)<strlen(source)) return NULL;
  while (*destination!='\0') {
    destination++;
  }
  while (*source!='\0') {
    *destination=*source;
    destination++;
    source++;
  }
  *destination='\0';
  return ret;

 }
const char* Strstr(const char* destination,const char* source)
 {
   assert(destination!=NULL&&source!=NULL);
   const char* black=destination;
   while (*black!='\0')
   {
     const char* red=black;
     const char* sub =source;
     while ((*red!='\0')&&(*sub!='\0')&&(*sub==*red))
     {
         red++;
         sub++;
     }
     if(*sub=='\0') return black;
     if(*red=='\0') return NULL;
     black++;
   }
  return NULL;
 }
int main(int argc, char const *argv[]) {
  /* code */
  char str1[100]="hello WorldwwwwwwwWORLDWorld!";
  char* str=NULL;
  int lenth=Strlen(str1);
  //printf("%d\n",lenth);
  const char* p=Strstr(str1,"WORLD");

  printf("%s\n",p);


  return 0;
}
