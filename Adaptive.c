uint8_t CMD (uint8_t distance)
{
    uint8_t x;
    if (distance >255 && distance <= 160)
    {
        UARTSend(inc);
        x = inc;
    }
    else if (distance < 160 && distance >= 90)
    {
        UARTSend(maintain);
        x = maintain;
    }
    else if (distance < 90 && distance >=20)
    {
        UARTSend(dec);
        x = dec;
    }
    else if (distance < 20 && distance >=5)
    {
        UARTSend(brake);
        x = brake;
    }
    else if (distance < 5 && distance > 0)
    {
        UARTSend(airbag);
        x = airbag;
    }
    UARTSend(distance);
    return x;
}





void show_state (uint8_t currState, uint8_t distance)
{
    switch (currState)
    {
        case inc:
            UARTSend("Increase Speed");            
            break;
            
        case dec:
            UARTSend("Decrease Speed");
            break;
            
        case maintain:
            UARTSend("Maintain Speed");
            break;
        
        case brake:
            UARTSend("Brake");
            break;
            
        case airbag:
            UARTSend("Airbag");
            break;
            
        default:
            break;
    }
    UARTSend(distance);
}
