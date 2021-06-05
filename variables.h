const int BLOCK_SIZE = 1024;
const double samplingFrequency = 44100;
double vReal[BLOCK_SIZE];
double vImag[BLOCK_SIZE];
int32_t samples[BLOCK_SIZE];
const int i2s_num = 0;
int retStat = 0;
int32_t sampleIn = 0;
double freq;
double ampli;
int array_of_hz[5000];
int hz;
int array_cnt = 0;
int buttonState;
int lastButtonState = HIGH; 
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;
int stop_recording = 0;
int lenght_frequency_array = 8; 
int array_of_notes_running[19];
int running_cnt = 0;
int chord_cnt = 0;
char array_of_chords[250];

//frequencies from B2 to F#/Gb3:
int frequency_array_1[] = {123, 131, 139, 147, 156, 165, 175, 185};
//frequencies from G3 to D4:
int frequency_array_2[] = {196, 208, 220, 233, 247, 261, 277, 294};
//frequencies from D#/Eb4 to A#/Bb4:
int frequency_array_3[] = {311, 330, 349, 370, 392, 415, 440, 466};
//frequencies from B4 to F#/Gb5:
int frequency_array_4[] = {494, 523, 554, 587, 622, 659, 698, 739};
//array for the notes:

i2s_config_t i2s_config = {
  mode: (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
  sample_rate: 44100,
  bits_per_sample: I2S_BITS_PER_SAMPLE_32BIT,
  channel_format: I2S_CHANNEL_FMT_ONLY_LEFT,
  communication_format: (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_LSB),
  intr_alloc_flags: ESP_INTR_FLAG_LEVEL1,
  dma_buf_count: 8,
  dma_buf_len : BLOCK_SIZE
};

i2s_pin_config_t pin_config = {
  .bck_io_num = 32, //this is BCK pin
  .ws_io_num = 33, // this is LRCK pin
  .data_out_num = I2S_PIN_NO_CHANGE, // this is DATA output pin
  .data_in_num = 27   //DATA IN
};
