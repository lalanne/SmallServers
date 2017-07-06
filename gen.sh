
message='<?xml version="1.0" encoding="ISO-8859-1"?><msg><header id_trans="1111" app="xml" user="ussd" passw="ussd" action="1"/><req><op>req_comp_promo</op><msisdn>56999694444</msisdn><idPromo>BO_80MB_2D</idPromo></req></msg>'

ip=127.0.0.1
port=4040

echo ${message} | netcat -w 10 ${ip} ${port}
