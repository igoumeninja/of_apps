#include "ofApp.h"

void ofApp::setup() {
  sender.setup(HOST, PORT);
  ofSetVerticalSync(true);

  plotHeight = 128;
  bufferSize = 512;

  fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING);
  // To use FFTW, try:
  //fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING, OF_FFT_FFTW);

  spectrogram.allocate(bufferSize, fft->getBinSize(), OF_IMAGE_GRAYSCALE);
  spectrogram.setColor(ofColor::black);
  spectrogramOffset = 0;

  drawBuffer.resize(bufferSize);
  middleBuffer.resize(bufferSize);
  audioBuffer.resize(bufferSize);
	
  drawBins.resize(fft->getBinSize());
  middleBins.resize(fft->getBinSize());
  audioBins.resize(fft->getBinSize());

  // 0 output channels,
  // 1 input channel
  // 44100 samples per second
  // [bins] samples per buffer
  // 4 num buffers (latency)

  ofSoundStreamSetup(0, 1, this, 44100, bufferSize, 4);

  mode = MIC;
  appWidth = ofGetWidth();
  appHeight = ofGetHeight();

  ofBackground(0, 0, 0);}

void ofApp::draw() {
  ofSetColor(255);
  ofPushMatrix();
  ofTranslate(16, 16);
  ofDrawBitmapString("Time Domain", 0, 0);
	
  soundMutex.lock();
  drawBuffer = middleBuffer;
  drawBins = middleBins;
  soundMutex.unlock();
	
  plot(drawBuffer, plotHeight / 2, 0);
  ofTranslate(0, plotHeight + 16);
  ofDrawBitmapString("Frequency Domain", 0, 0);
  plot(drawBins, -plotHeight, plotHeight / 2);
  ofTranslate(0, plotHeight + 16);
  spectrogram.update();
  spectrogram.draw(0, 0);
  ofDrawRectangle(0, 0, bufferSize, bufferSize / 2);
  ofDrawBitmapString("Spectrogram", 0, 0);
  ofPopMatrix();
  string msg = ofToString((int) ofGetFrameRate()) + " fps";
  ofDrawBitmapString(msg, appWidth - 80, appHeight - 20);
}

float powFreq(float i) {
  return powf(i, 3);
}

void ofApp::plot(vector<float>& buffer, float scale, float offset) {
  ofNoFill();
  int n = buffer.size();
  ofDrawRectangle(0, 0, n, plotHeight);
  glPushMatrix();
  glTranslatef(0, plotHeight / 2 + offset, 0);
  ofBeginShape();
  for (int i = 0; i < n; i++) {
    ofVertex(i, buffer[i] * scale);
  }
  ofEndShape();
  glPopMatrix();
}

void ofApp::audioReceived(float* input, int bufferSize, int nChannels) {
  if (mode == MIC) {
    // store input in audioInput buffer
    memcpy(&audioBuffer[0], input, sizeof(float) * bufferSize);
		
    float maxValue = 0;
    for(int i = 0; i < bufferSize; i++) {
      if(abs(audioBuffer[i]) > maxValue) {
        maxValue = abs(audioBuffer[i]);
      }
    }
    for(int i = 0; i < bufferSize; i++) {
      audioBuffer[i] /= maxValue;
    }
		
  } else if (mode == NOISE) {
    for (int i = 0; i < bufferSize; i++)
      audioBuffer[i] = ofRandom(-1, 1);
  } else if (mode == SINE) {
    for (int i = 0; i < bufferSize; i++)
      audioBuffer[i] = sinf(PI * i * mouseX / appWidth);
  }
	
  fft->setSignal(&audioBuffer[0]);

  float* curFft = fft->getAmplitude();
  memcpy(&audioBins[0], curFft, sizeof(float) * fft->getBinSize());

  float maxValue = 0;
  for(int i = 0; i < fft->getBinSize(); i++) {
    if(abs(audioBins[i]) > maxValue) {
      maxValue = abs(audioBins[i]);
    }
  }
  for(int i = 0; i < fft->getBinSize(); i++) {
    audioBins[i] /= maxValue;
  }
	
  int spectrogramWidth = (int) spectrogram.getWidth();
  int n = (int) spectrogram.getHeight();

  cout << n << endl;
  ofxOscMessage m;
  m.setAddress("/testaki");
  for(int i = 0; i < n; i++) {
    int j = (n - i - 1) * spectrogramWidth + spectrogramOffset;
    int logi = ofMap(powFreq(i), powFreq(0), powFreq(n), 0, n);
    spectrogram.setColor(j, (unsigned char) (255. * audioBins[logi]));
    m.addFloatArg(audioBins[logi]);
  }
  sender.sendMessage(m, false);

  spectrogramOffset = (spectrogramOffset + 1) % spectrogramWidth;
	
  soundMutex.lock();
  middleBuffer = audioBuffer;
  middleBins = audioBins;
  soundMutex.unlock();
}

void ofApp::keyPressed(int key){
  switch (key) {
    case 'm':
      mode = MIC;
      break;
    case 'n':
      mode = NOISE;
      break;
    case 's':
      mode = SINE;
      break;
  }
	// send a test message
	if(key == 'a' || key == 'A'){
		ofxOscMessage m;
		m.setAddress("/test");
		m.addIntArg(1);
		m.addFloatArg(3.5f);
		m.addStringArg("hello");
		m.addFloatArg(ofGetElapsedTimef());
		sender.sendMessage(m, false);
	}

	// send an image
	// note: the size of the image depends greatly on your network buffer sizes,
	// if an image is too big the message won't come through and you may need
	// to break it up into multiple blobs
	if(key == 'i' || key == 'I'){

		// load image from buffer
		img.load(imgAsBuffer);

		// send as a binary blob
		ofxOscMessage m;
		m.setAddress("/image");
		m.addBlobArg(imgAsBuffer);
		sender.sendMessage(m);
		ofLog() << "sending image with size: " << imgAsBuffer.size();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  ofxOscMessage m;
  m.setAddress("/testaki");
  m.addIntArg(1);
  m.addStringArg("down");
  sender.sendMessage(m, false);
  
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	ofxOscMessage m;
	m.setAddress("/mouse/button");
	m.addIntArg(0);
	m.addStringArg("up");
	sender.sendMessage(m, false);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
