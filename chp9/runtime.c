#undef __STDC__
#include <stdio.h>


int *initArray(int size, int init)
{int i;
 int *a = (int *)malloc(size*sizeof(int));
 for(i=0;i<size;i++) a[i]=init;
 return a;
}

int *allocRecord(int size)
{int i;
 int *p, *a;
 p = a = (int *)malloc(size);
 for(i=0;i<size;i+=sizeof(int)) *p++ = 0;
 return a;
}

struct string {int length; unsigned char chars[1];};

int stringEqual(struct string *s, struct string *t)
{int i;
 if (s==t) return 1;
 if (s->length!=t->length) return 0;
 for(i=0;i<s->length;i++) if (s->chars[i]!=t->chars[i]) return 0;
 return 1;
}

int mystrcmp(struct string *s1, struct string* s2, int flag)
{int i;
 if (flag < 0 || flag > 5) return 0; // TODO error
 if (flag == 0 || flag == 1) {
  if (s1->length != s2->length)
   return 0;
  for (i = 0; i < s1->length; i++) {
    if (flag == 0 && s1->chars[i] != s2->chars[i]) return 0;
    if (flag == 1 && s1->chars[i] != s2->chars[i]) return 1;
    if (flag == 1 && s1->chars[i] == s2->chars[i]) return 0;
  }
  if (flag == 0) return 1;
  return 0;
 } else {
  int m = 0;
  if (s1->length > s2->length) m = s1->length;
  else m = s2->length;
  for (i = 0; i < malloc; i++) {
    if (s1->chars[i] <= s2->chars[i]) { if (flag == 2) return 1; else return 0; }
    if (s1->chars[i] <  s2->chars[i]) { if (flag == 3) return 1; else return 0; }
    if (s1->chars[i] >= s2->chars[i]) { if (flag == 4) return 1; else return 0; }
    if (s1->chars[i] >  s2->chars[i]) { if (flag == 5) return 1; else return 0; }
  }
  if (s1->length == s2->length) // Reached the end and they're
    return 0;                   // same length, so they're equal.
  return 0;
 }

}

void print(struct string *s)
{int i; unsigned char *p=s->chars;
 for(i=0;i<s->length;i++,p++) putchar(*p);
}

void flush()
{
 fflush(stdout);
}

struct string consts[256];
struct string empty={0,""};

int main()
{int i;
 for(i=0;i<256;i++)
   {consts[i].length=1;
    consts[i].chars[0]=i;
   }
 return tigermain(0 /* static link!? */);
}

int ord(struct string *s)
{
 if (s->length==0) return -1;
 else return s->chars[0];
}

struct string *chr(int i)
{
 if (i<0 || i>=256)
   {printf("chr(%d) out of range\n",i); exit(1);}
 return consts+i;
}

int size(struct string *s)
{
 return s->length;
}

struct string *substring(struct string *s, int first, int n)
{
 if (first<0 || first+n>s->length)
   {printf("substring([%d],%d,%d) out of range\n",s->length,first,n);
    exit(1);}
 if (n==1) return consts+s->chars[first];
 {struct string *t = (struct string *)malloc(sizeof(int)+n);
  int i;
  t->length=n;
  for(i=0;i<n;i++) t->chars[i]=s->chars[first+i];
  return t;
 }
}

struct string *concat(struct string *a, struct string *b)
{
 if (a->length==0) return b;
 else if (b->length==0) return a;
 else {int i, n=a->length+b->length;
       struct string *t = (struct string *)malloc(sizeof(int)+n);
       t->length=n;
       for (i=0;i<a->length;i++)
	 t->chars[i]=a->chars[i];
       for(i=0;i<b->length;i++)
	 t->chars[i+a->length]=b->chars[i];
       return t;
     }
}

int not(int i)
{ return !i;
}

#undef getchar

struct string *getchar()
{int i=getc(stdin);
 if (i==EOF) return &empty;
 else return consts+i;
}
