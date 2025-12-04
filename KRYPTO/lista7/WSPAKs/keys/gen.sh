openssl req -new -key key.pem -out csr.pem \
  -subj "/C=PL/ST=DS/L=Wroclaw/O=KryptoOrg/CN=client.supersafe.pl"

openssl x509 -req -in csr.pem \
  -CA ../ca_keys/ca_cert.pem -CAkey ../ca_keys/ca_key.pem \
  -CAcreateserial -out cert.pem

# openssl verify -CAfile ../ca_keys/ca_cert.pem cert.pem
