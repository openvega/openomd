# openomd
Open source OMD parser

openomd is an open source OMD-C and OMD-D parser supports HKEx market data protocol. It is written in C++ and use simple binary protocol, target to be high performance.

### Build
To build the unit test you will need maven (java) and C++ compiler. Currently supports VS2017 and g++ 7.3.1
```sh
$ mvn clean test
```

You could download the library or use nar-maven plugin to embed the library into your project.
```sh
  <dependency>
    <groupId>io.github.openvega</groupId>
    <artifactId>openomd</artifactId>
    <version>1.0.0</version>
    <type>nar</type>
  </dependency>
```