# Documentation

3C 02 08 FC 00 79 01 D7 00 13 00 22 1B 03 30 02 18 


Prüfsumme	B17=Einheit_8(3Ch+02h+08h+0FCh+00h+79h+01h+D7h+00h+13h+00h+22h+1Bh+03h+30h+02h)=18h
CO2	B3 * 256 + B4 = 08h * 256 + 0FCh = 2300ppm
eCO2	B5*256+B6=00h*256+79h=121ug/m3
TVOC	B7*256+B8=01h*256+0D7h=471ug/m3
PM2.5	B9*256+B10=00h*256+13h=19ug/m3
PM10	B11*256+B12=00h*256+22h=34ug/m3
Temperaturinteger	B13=1Bh=27℃
Decimaltemperature	B14*0,1=03h*0,1=0,3℃
Feuchtigkeitinteger	B15=30h=48%rF
Feuchtigkeitdecimal	B16*0,1=02h*0,1=0,2 %rF
