#include <stdio.h>

int sum(int* array, int size)
{
  int ret;
  int tmp;
  int i = 0;

/************************************
*  for(int i = 0; i < size; i++) {
*    ret += array[i];
*  }
************************************/
  asm volatile (
    "loop: \t\n"
      "mov (%[array], %[i], 4), %[tmp] \t\n"  // array[i]の値をtmpに格納  arrayの先頭ptr+(i*4byte)の値 → tmp
      "add %[tmp], %[ret] \t\n"     // ret += tmp
      "add $0x01, %[i] \t\n"        // i++
      "cmp %[i], %[size] \t\n"      // i < size の結果をステータスレジスタに格納
      "ja loop \t\n"                     // i < size がtrueならloopラベルにジャンプ
    :[ret]"=&r"(ret), [tmp]"+&r"(tmp), [i]"+&r"(i)
    :[array]"r"(array), [size]"r"(size)
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

