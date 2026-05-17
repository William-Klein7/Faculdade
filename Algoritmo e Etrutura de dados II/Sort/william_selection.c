#include <stdio.h>
#define tam 14

void selection_sort(int arr[], int n)
{
  int i, j, min_idx;

  for (i = 0; i < n - 1; i++)
  {
    min_idx = i;
    for (j = i + 1; j < n; j++)
      if (arr[j] < arr[min_idx])
        min_idx = j;

    int temp = arr[min_idx];
    arr[min_idx] = arr[i];
    arr[i] = temp;
  }
}

int main()
{
  int arr[] = {5, 10, 11, 3, 4, 1, 13, 15, 2, 20, 16, 7, 19, 14};

  printf("Array antes da ordenacao: \n");
  for (int i = 0; i < tam; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");

  selection_sort(arr, tam);

  printf("Array apos a ordenacao: \n");
  for (int i = 0; i < tam; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");

  return 0;
}