byte b;
int rs = 0;
int sys_n, cmd_n;
int first_byte_x, second_byte_x, x;

void setup()
{
  Serial.begin(9600);

}

void log()
{
  Serial.println("\nb\trs\tsys_n\tcmd_n\n");
  Serial.print(b);  Serial.print("\t");
  Serial.print(rs);  Serial.print("\t");
  Serial.print(sys_n);  Serial.print("\t");
  Serial.print(cmd_n);  Serial.print("\t");

  Serial.print("\n");
}

void loop()
{

  if (Serial.available() > 0)
  {
    b = Serial.read(); 
       
    switch (rs)
    {
      case 0:
        if (b == 48) rs++;
        else Serial.println("-+-+-+-\tnot first synchro\t-+-+-+-");
        break;
      case 1:
        if (b == 48) rs++;
        else
        {
          rs = 0;
          Serial.println("-+-+-+-\tnot second synchro\t-+-+-+-");
        }
        break;
      case 2:
        sys_n = b;
        rs++;
        break;   
      case 3:
        cmd_n = b;
        rs++;
        break;
      case 4:
        switch (sys_n)
        {
          case 49://engines system
            switch (cmd_n)
            {
              /*case 49://position x, y, z
                switch (rs)
                {
                  case 5:
                    first_byte_x = b;
                    rs++;
                    break;
                  case 6:
                    second_byte_x = b;
                    x = first_byte_x;
                    x = x << 8;
                    x = x | second_byte_x;
                    rs=0;                    
                    break;
//                  case 7:
//                    first_byte_y = b;
//                    rs++;
//                    break;
//                  case 8:
//                    second_byte_y = b;
//                    rs++;
//                    break;
//                  case 9:
//                    first_byte_z = b;
//                    rs++;
//                    break;
//                  case 10:
//                    second_byte_z = b;
//                    rs++;
//                    break;
//                  case 11:
//                    
//                    rs++;
//                    break;
//                  case 12:
//                    y = first_byte_y;
//                    y = y << 8;
//                    y = y | second_byte_y;
//                    rs++;
//                    break;
//                  case 13:
//                    z = first_byte_z;
//                    z = z << 8;
//                    z = z | second_byte_z;
//                    rs++;
//                    break;
                }*/
              default:
                Serial.println("-+-+-+-\tnumber command  not found\t-+-+-+-");
            }
            break;
            
          default:
            Serial.println("-+-+-+-\tnumber system  not found\t-+-+-+-");
        }
//        rs++;//for case 5 and 6
        rs = 0;
        break;
      /*case 5:
        if (b == 102) rs++;
        else
        {
          rs = 0;
          Serial.println("-+-+-+-\tnot first end synchro\t-+-+-+-");
        }
        break;
      case 6:
        rs = 0;
        if (b == 102) Serial.println("-+-+-+-\tcommand successful recive\t-+-+-+-");
        else  Serial.println("-+-+-+-\tnot second end synchro\t-+-+-+-");
        break;*/
    }
    log();
    
  }
  else
  {
//    Serial.println("any work");
//    delay(3000);
    switch(sys_n)
    {
      case 49:
        switch(cmd_n)
        {
          case 49:
            Serial.println("inicialization");
            cmd_n = 0;//not now
            break;

          default:
            Serial.println("command not selected");
            delay(3000);
        }
        break;
        
      default:
        Serial.println("system not selected");
        delay(3000);
    }
  }

}
