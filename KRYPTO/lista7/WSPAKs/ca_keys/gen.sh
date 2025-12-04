openssl x509 -new -key ./ca_key.pem -out ca_cert.pem \
  -extfile ./ca.cnf -extensions extensions \
  -set_subject "/C=PL/ST=DS/L=Wroclaw/O=KryptoOrg/CN=supersafe.pl"
