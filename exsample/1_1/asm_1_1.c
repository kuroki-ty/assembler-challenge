#include <stdio.h>

int sum(int* array, int size)
{
  int ret;
  int tmp;

/************************************
*  for(int i = 0; i < size; i++) {
*    ret += array[i];
*  }
************************************/
  asm volatile (
    "loop: \t\n"
      "mov (%[array]), %[tmp] \t\n"  // arrayポインタの中身をtmpに格納
      "add %[tmp], %[ret] \t\n"      // ret += tmp;
      "add $0x04, %[array] \t\n"     // array++;
      "sub $0x01, %[size] \t\n"      // size--;
      "jnz loop \t\n"                // size != 0 がtrueならloopラベルにジャンプ
    :[ret]"=&r"(ret), [tmp]"+r"(tmp), [array]"+r"(array), [size]"+r"(size)
    :
  );

  return ret;
}

int main(void)
{
  int array[5] = {1, 2, 3, 4, 5};
  int size = 5;
  int val = sum(array, size);

  printf("%d\n", val);

  return 0;
}

