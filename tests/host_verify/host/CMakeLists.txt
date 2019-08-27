# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License.

add_executable(test_host_verify host.cpp)

# Create private/public key pairs using openssl
add_custom_command(OUTPUT keyec.pem publicec.pem
  COMMAND openssl ecparam -name prime256v1 -genkey -noout -out keyec.pem
  COMMAND openssl ec -in keyec.pem -pubout -out publicec.pem)
add_custom_command(OUTPUT keyrsa.pem publicrsa.pem
  COMMAND openssl genrsa -out keyrsa.pem 2048
  COMMAND openssl rsa -in keyrsa.pem -outform PEM -pubout -out publicrsa.pem)

if (OE_SGX)
  add_custom_target(sgx_ec_cert
    COMMAND oecert
            $<TARGET_FILE:oecert_enc>
            --cert keyec.pem publicec.pem --out sgx_cert_ec.der
    DEPENDS oecert_enc keyec.pem publicec.pem)
  add_custom_target(sgx_rsa_cert
    COMMAND oecert
            $<TARGET_FILE:oecert_enc>
            --cert keyrsa.pem publicrsa.pem --out sgx_cert_rsa.der
    DEPENDS oecert_enc keyrsa.pem publicrsa.pem)
  add_custom_target(sgx_report
    COMMAND oecert
            $<TARGET_FILE:oecert_enc>
            --report --out sgx_report.bin
    DEPENDS oecert_enc)
  add_dependencies(test_host_verify sgx_ec_cert sgx_rsa_cert sgx_report)
else()
  # TODO: Test running in non-SGX machine.  Need to get report from an SGX machine.
  # 1. Create ACCVM and connect to it.
  # 2. Run the above commands to generate the keys/certs/reports.
  # 3. Copy over the certs and report.
endif()

# Copy bad test data
configure_file(../data/sgx_cert_ec_bad.der
               ${CMAKE_CURRENT_BINARY_DIR}/sgx_cert_ec_bad.der COPYONLY)
configure_file(../data/sgx_cert_rsa_bad.der
               ${CMAKE_CURRENT_BINARY_DIR}/sgx_cert_rsa_bad.der COPYONLY)
configure_file(../data/sgx_report_bad.bin
               ${CMAKE_CURRENT_BINARY_DIR}/sgx_report_bad.bin COPYONLY)

target_link_libraries(test_host_verify oehostverify)
