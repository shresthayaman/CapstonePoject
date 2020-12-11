#define MAX_DELAY 300


void AddDistortion(void){
    threshold = MAX_INPUT_VALUE
    unsigned int[] effectArray[size] = {};
    unsigned int ADC_low = find_minimum(array, size);
    unsigned int ADC_high = find_maximum(array,size);

    for(int i = 0; i<size; i++){
       int curVal =  ((array[i] <<8 ) | ADC_low ) + 0x8000  //converts into signed 16 bit value
        if(curVal > threshold){
            currrVal = 32768;
        }
        effectArray[i] = curValue;

    }

    return effectArray;

}

unsigned int[] AddFuzz(unsigned int[] array, int size){
    threshold = MAX_INPUT_VALUE
    unsigned int[] effectArray[size] = {};
    unsigned int ADC_low = find_minimum(array, size);
    unsigned int ADC_high = find_maximum(array,size);

    for(int i = 0; i<size; i++){
        int curVal =  ((array[i] <<8 ) | ADC_low ) + 0x8000  //converts into signed 16 bit value
        if(curVal > threshold){
            currrVal = 32768;
        }
        if(currVal < -threshold){
            curVal = -32768;
        }
        effectArray[i] = curValue;

    }

    return effectArray;



}

unsigned int[] AddOverdrive(unsigned int[] array, int size){
    threshold = MAX_INPUT_VALUE
    unsigned int[] effectArray[size] = {0};
    unsigned int ADC_low = find_minimum(array, size);
        unsigned int ADC_high = find_maximum(array,size);

    for(int i = 0; i<size; i++){
        int curVal =  ((array[i] <<8 ) | ADC_low) + 0x8000  //converts into signed 16 bit value
        //the amplitude of the input signal is modified by the threshold value
        curVal = map(input, -32768, +32768,-threshold, threshold)  //essentially switching the upper and lower bounds of the input to the desired values to achieve the overdrive effects

        effectArray[i]= curVal;
    }
}

unsigned int[] AddDelay(unsigned int[] array, int size){
    threshold = MAX_INPUT_VALUE
    unsigned int[] effectArray[size] = {0};
    byte DelayBuffer[MAX_DELAY];
    unsigned int DelayCounter = 0;
    unsigned int Delay_Depth = MAX_DELAY;
    unsigned int ADC_low = find_minimum(array, size);
    unsigned int ADC_high = find_maximum(array,size);

    DelayBuffer[DelayCounter] = ADC_high; //store high bit
    for(int i = 0; i<size; i++){
        DelayCounter++;
        if(DelayCounter >= Delay_Depth){
            DelayCounter = 0;
        }
        curVal = (((DelayBuffer[DelayCounter] << 8) | ADC_low) + 0x8000)+(((ADC_high << 8) | ADC_low) + 0x8000); // make a signed 16b value
        effectArray[i] = curVal;
    }

    return effectArray;


}

unsigned int find_minimum(unsigned int a[], int n) {
  int c, index = 0;

  min = 4294967295;
  for (c = 1; c < n; c++)
    if (a[c] < min)
      index = c;

  return a[index];
}

unsigned int find_maximum(int a[], int n) {
  int c, index = 0;
  max = 0;
  for (c = 1; c < n; c++)
    if (a[c] > max)
      index = c;

  return a[index];
}


