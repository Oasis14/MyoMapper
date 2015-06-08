int[] EMG = new int[8];

int yaw, pitch, roll;
int intesity = 0;

float orX, ORx, ORX = 0;
float orY, ORy, ORY = 0;
float orZ, ORz, ORZ = 0;
int intensity = 0;

void myoOn(Myo.Event event, Device myo, long timestamp) {
  
  switch(event) {
  case PAIR:
    println("myoOn PAIR");
    break;
  case UNPAIR:
    println("myoOn UNPAIR");
    break;
  case CONNECT:
    println("myoOn CONNECT");
    break;
  case DISCONNECT:
    println("myoOn DISCONNECT");
    break;
  case ARM_SYNC:
    println("myoOn ARM_SYNC");
    OscMessage sync = new OscMessage("/sync");
    sync.add(myo.getArm());
    sync.add(myo.getFirmware());
    oscP5.send(sync, myRemoteLocation);
    break;
  case ARM_UNSYNC:
    println("myoOn ARM_UNSYNC");
    break;
  case POSE:
    println("myoOn POSE");
//    OscMessage Pose = new OscMessage("/pose");
    pose = myo.getPose();
//    Pose.add(myo.getPose());
//    oscP5.send(Pose, myRemoteLocation);
    break;
 
  case ORIENTATION:
   OscMessage orientS = new OscMessage("/orientationS");
   OscMessage orient = new OscMessage("/orientation");

    // println("myoOn ORIENTATION");
     PVector orientation = myo.getOrientation();
     
    orX = orientation.x; // orientation.y (roll) original value
    orY = orientation.y; // orientation.y (pitch) original value
    orZ = orientation.z; // orientation.z (yaw) original value
   
    ORZ = ORz-(orZ-0.5); // centering YAW
    ORY = ORy-(orY-0.5); // centering PITCH
    ORX = ORx-(orX-0.5); // centering ROLL

    println(ORz);
    println(ORX);
    /* 
    ORZ = orZ-ORz-0.5; // centering YAW
    ORY = orY-ORY-0.5; // centering PITCH
    ORX = orX-ORX-0.5; // centering ROLL

   */ 
    if(ORZ<0) {ORZ = 1+ORZ;}
    else if (ORZ>1) {ORZ = 1-ORZ;}
    else  {ORZ = ORZ;}
    
    if(ORY<0) {ORY = 1+ORY;}
    else if (ORY>1) {ORY = 1-ORY;}
    else  {ORY = ORY;}
    
    if(ORX<0) {ORX = 1+ORX;}
    else if (ORX>1) {ORX = 1-ORX;}
    else  {ORX = ORX;}  
    
    
    roll = int(abs(ORX-reverseRoll)*255); // reverse + scale
    pitch = int(abs(ORY-reversePitch)*255); // reverse + scale
    yaw = int(abs(ORZ-reverseYaw)*255); // reverse + scale
      
    orientS.add(yaw);
    orientS.add(pitch);
    orientS.add(roll);

    orientS.add(orientation.x);
    orientS.add(orientation.y);
    orientS.add(orientation.z);
 
    oscP5.send(orient, myRemoteLocation);   
    oscP5.send(orientS, myRemoteLocation);


    break;
 
  case ACCELEROMETER:
    // println("myoOn ACCELEROMETER");
      PVector acceleration = myo.getAccelerometer();
//   println("acceleration" + acceleration.x + " " + acceleration.y + " " + acceleration.z);
/*      OscMessage accelerometer = new OscMessage("/acceleration0");
    accelerometer.add(acceleration.x);
    accelerometer.add(acceleration.y);
    accelerometer.add(acceleration.z);
   oscP5.send(accelerometer, myRemoteLocation); 
*/
    break;
 
  case GYROSCOPE:
    // println("myoOn GYROSCOPE");
      PVector gyro = myo.getGyroscope();
/*    println("acceleration" + acceleration.x + " " + acceleration.y + " " + acceleration.z);
    OscMessage gyroscope = new OscMessage("/gyro0");
    gyroscope.add(gyro.x);
    gyroscope.add(gyro.y);
    gyroscope.add(gyro.z);
    oscP5.send(gyroscope, myRemoteLocation); 
 */
    break;
 
  case RSSI:
    println("myoOn RSSI");
    break;
 
  case EMG:  
      int emgSum = 0;
      int emg[] = myo.getEmg(); // array of EMG data
     
 //     OscMessage Emg = new OscMessage("/emg0");
      OscMessage emgAvg = new OscMessage("/emgAvg");
      OscMessage Emg = new OscMessage("/emg");

      for(int i=0; i<8; i++){
      EMG[i]= abs(emg[i])+127; // rescale EMG data
      emgSum = EMG[i] + emgSum; // EMG sum for avg calculation
      emg[i] = abs(emg[i]);  // add emg value to /emg0 message
      }
     
      intensity = abs(emgSum/8-reverseEmg); // average calculation
      emgAvg.add(intensity);
      Emg.add(emg);
    
 //     println("Intesity: "+intensity);

  //    oscP5.send(Emg, myRemoteLocation);
      oscP5.send(emgAvg, myRemoteLocation);
      oscP5.send(Emg, myRemoteLocation);

    break;
  }
}