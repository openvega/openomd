# openomd
Open source OMD handler

openomd is an open source OMD-C and OMD-D handler supports HKEx market data protocol. It is written in C++ and use **[Simple Binary Protocol](https://github.com/real-logic/simple-binary-encoding)**, target to be high performance.

### Build
Requirement: java-jre(1.7+), maven (3.3.3+), C++ compiler(Currently supports VS2017 and g++ 7.3.1) for unit test.
#### Generate sbe messages
OMD is almost compatiable with SBE protocol except the **[Group](https://github.com/real-logic/simple-binary-encoding/wiki/FIX-SBE-XML-Primer#group-element)** field. OMD group field only contains **number in group** but SBE contains **block length** and **number in group**. That means we have to patch the messages with Group. All the message classes in the repo has been patched(overwrite by *.sbeomdhack files), but in case you need to generate the sbe message classes again, please follow below steps:
1. In openomd_handler module, generate sbe classes
```sh
openomd/openomd_handler> mvn -f pom-gen.xml install
```
2. **Import** If updated messages contain Group element, update the patch file (*.sbeomdhack) manually
3. patch message files by running
```sh
openomd/openomd_handler> bash omdpatch.sh
```
#### Build unit test
```sh
$ mvn test
```

You could download the library or use nar-maven plugin to embed the library into your project.
```sh
  <dependency>
    <groupId>io.github.openvega</groupId>
    <artifactId>openomd</artifactId>
    <version>1.0.4</version>
    <type>nar</type>
  </dependency>
```1
