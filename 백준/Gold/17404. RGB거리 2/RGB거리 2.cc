#include <stdio.h>
#include <malloc.h>

struct ColorType {
  
  int Red;
  int Green;
  int Blue;
};

int CalcuclateMinCost (struct ColorType* house, int length, int resultPosition);

int main (int argc, char* argv[]) {
  
  int length = 0;
  scanf ("%d", &length);
  
  struct ColorType* house = (struct ColorType*) malloc (length * sizeof (struct ColorType));
  if (house == NULL) return -1;
  
  for (int index = 0; index < length; index++) {
    
    int red = 0, green = 0, blue = 0;
    scanf ("%d%d%d", &red, &green, &blue);
    
    house[index].Red = red;
    house[index].Green = green;
    house[index].Blue = blue;
  }
  
  struct ColorType Null = { 987654321, 987654321, 987654321 };
  int temp[3] = { house[0].Red, house[0].Green, house[0].Blue };
  house[0] = Null;
  
  int result = 987654321;
  for (int start = 0; start < 3; start++) {
    
    if (start == 0) house[0].Red = temp[start];
    else if (start == 1) house[0].Green = temp[start];
    else house[0].Blue = temp[start];
    
    for (int end = 0; end < 3; end++) {
      
      if (start == end) continue;
      
      int value = CalcuclateMinCost (house, length, end);
      if (result > value) result = value;
    }
    
    house[0] = Null;
  }
  
  printf ("%d", result);
  free ((struct ColorType*) house);
  return 0;
}

int Minimum (int first, int second) {
  
  return first < second ? first : second;
}

int CalcuclateMinCost (struct ColorType* house, int length, int resultPosition) {
  
  if (house == NULL) return -1;
  
  struct ColorType* table = (struct ColorType*) calloc (length, sizeof (struct ColorType));
  if (table == NULL) return -2;
  
  table[0] = house[0];
  for (int index = 1; index < length; index++) {
    
    int position = index - 1;
    table[index].Red = house[index].Red + Minimum (table[position].Green, table[position].Blue);
    table[index].Green = house[index].Green + Minimum (table[position].Red, table[position].Blue);
    table[index].Blue = house[index].Blue + Minimum (table[position].Red, table[position].Green);
  }
  
  int result = 0;
  if (resultPosition == 0) result = table[length - 1].Red;
  else if (resultPosition == 1) result = table[length - 1].Green;
  else result = table[length - 1].Blue;
  
  free ((struct ColorType*) table);
  return result;
}