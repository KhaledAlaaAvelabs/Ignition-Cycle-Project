uint8_t CMD (uint8_t distance)
{
    uint8_t x;
    if (distance >255 && distance <= 160)
    {
        send_Uart(inc);
        x = inc;
    }
    else if (distance < 160 && distance >= 90)
    {
        send_Uart(maintain);
        x = maintain;
    }
    else if (distance < 90 && distance >=20)
    {
        send_Uart(dec);
        x = dec;
    }
    else if (distance < 20 && distance >=5)
    {
        send_Uart(brake);
        x = brake;
    }
    else if (distance < 5 && distance > 0)
    {
        send_Uart(airbag);
        x = airbag;
    }
    send_Uart(distance);
    return x;
}





void show_state (uint8_t currState, uint8_t distance)
{
    switch (currState)
    {
        case inc:
            send_Uart("Increase Speed");            
            break;
            
        case dec:
            send_Uart("Decrease Speed");
            break;
            
        case maintain:
            send_Uart("Maintain Speed");
            break;
        
        case brake:
            send_Uart("Brake");
            break;
            
        case airbag:
            send_Uart("Airbag");
            break;
            
        default:
            break;
    }
    send_Uart(distance);
}
