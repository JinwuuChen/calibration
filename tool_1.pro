#-------------------------------------------------
#
# Project created by QtCreator 2022-12-01T14:17:16
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += "-mssse3"
QMAKE_CXXFLAGS += "-msse4.1"
QMAKE_CXXFLAGS += "-mavx2"
QMAKE_CXXFLAGS += "-mpclmul"
QMAKE_CXXFLAGS += "-maes"
QMAKE_CXXFLAGS += "-msha"
# 支持OpenMP特性，发挥算法的最大潜能
LIBS += -lgomp -lpthread
QMAKE_CXXFLAGS += "-fopenmp"
TARGET = tool_1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        calibration.cpp \
    camera.cpp \
    cam_neican.cpp \
    nameimg.cpp \
    setboard.cpp \
    camera_neican_help.cpp \
    newcamerproject.cpp \
    savecamerresult.cpp \
    external_camera.cpp\
    camerawithlidar.cpp \
    lidarwithlidar.cpp\
    graphicsview.cpp \
    imagebox.cpp\
    tools/cryptopp/include/3way.cpp \
    tools/cryptopp/include/adhoc.cpp \
    tools/cryptopp/include/adler32.cpp \
    tools/cryptopp/include/algebra.cpp \
    tools/cryptopp/include/algparam.cpp \
    tools/cryptopp/include/allocate.cpp \
    tools/cryptopp/include/arc4.cpp \
    tools/cryptopp/include/aria.cpp \
    tools/cryptopp/include/aria_simd.cpp \
    tools/cryptopp/include/ariatab.cpp \
    tools/cryptopp/include/asn.cpp \
    tools/cryptopp/include/authenc.cpp \
    tools/cryptopp/include/base32.cpp \
    tools/cryptopp/include/base64.cpp \
    tools/cryptopp/include/basecode.cpp \
    tools/cryptopp/include/bench1.cpp \
    tools/cryptopp/include/bench2.cpp \
    tools/cryptopp/include/bench3.cpp \
    tools/cryptopp/include/bfinit.cpp \
    tools/cryptopp/include/blake2.cpp \
    tools/cryptopp/include/blake2b_simd.cpp \
    tools/cryptopp/include/blake2s_simd.cpp \
    tools/cryptopp/include/blowfish.cpp \
    tools/cryptopp/include/blumshub.cpp \
    tools/cryptopp/include/camellia.cpp \
    tools/cryptopp/include/cast.cpp \
    tools/cryptopp/include/casts.cpp \
    tools/cryptopp/include/cbcmac.cpp \
    tools/cryptopp/include/ccm.cpp \
    tools/cryptopp/include/chacha.cpp \
    tools/cryptopp/include/chacha_avx.cpp \
    tools/cryptopp/include/chacha_simd.cpp \
    tools/cryptopp/include/chachapoly.cpp \
    tools/cryptopp/include/cham.cpp \
    tools/cryptopp/include/cham_simd.cpp \
    tools/cryptopp/include/channels.cpp \
    tools/cryptopp/include/cmac.cpp \
    tools/cryptopp/include/cpu.cpp \
    tools/cryptopp/include/crc.cpp \
    tools/cryptopp/include/crc_simd.cpp \
    tools/cryptopp/include/cryptlib.cpp \
    tools/cryptopp/include/darn.cpp \
    tools/cryptopp/include/datatest.cpp \
    tools/cryptopp/include/default.cpp \
    tools/cryptopp/include/des.cpp \
    tools/cryptopp/include/dessp.cpp \
    tools/cryptopp/include/dh.cpp \
    tools/cryptopp/include/dh2.cpp \
    tools/cryptopp/include/dll.cpp \
    tools/cryptopp/include/dlltest.cpp \
    tools/cryptopp/include/donna_32.cpp \
    tools/cryptopp/include/donna_64.cpp \
    tools/cryptopp/include/donna_sse.cpp \
    tools/cryptopp/include/dsa.cpp \
    tools/cryptopp/include/eax.cpp \
    tools/cryptopp/include/ec2n.cpp \
    tools/cryptopp/include/eccrypto.cpp \
    tools/cryptopp/include/ecp.cpp \
    tools/cryptopp/include/elgamal.cpp \
    tools/cryptopp/include/emsa2.cpp \
    tools/cryptopp/include/eprecomp.cpp \
    tools/cryptopp/include/esign.cpp \
    tools/cryptopp/include/files.cpp \
    tools/cryptopp/include/filters.cpp \
    tools/cryptopp/include/fips140.cpp \
    tools/cryptopp/include/fipsalgt.cpp \
    tools/cryptopp/include/fipstest.cpp \
    tools/cryptopp/include/gcm.cpp \
    tools/cryptopp/include/gcm_simd.cpp \
    tools/cryptopp/include/gf256.cpp \
    tools/cryptopp/include/gf2_32.cpp \
    tools/cryptopp/include/gf2n.cpp \
    tools/cryptopp/include/gf2n_simd.cpp \
    tools/cryptopp/include/gfpcrypt.cpp \
    tools/cryptopp/include/gost.cpp \
    tools/cryptopp/include/gzip.cpp \
    tools/cryptopp/include/hc128.cpp \
    tools/cryptopp/include/hc256.cpp \
    tools/cryptopp/include/hex.cpp \
    tools/cryptopp/include/hight.cpp \
    tools/cryptopp/include/hmac.cpp \
    tools/cryptopp/include/hrtimer.cpp \
    tools/cryptopp/include/ida.cpp \
    tools/cryptopp/include/idea.cpp \
    tools/cryptopp/include/integer.cpp \
    tools/cryptopp/include/iterhash.cpp \
    tools/cryptopp/include/kalyna.cpp \
    tools/cryptopp/include/kalynatab.cpp \
    tools/cryptopp/include/keccak.cpp \
    tools/cryptopp/include/keccak_core.cpp \
    tools/cryptopp/include/keccak_simd.cpp \
    tools/cryptopp/include/lea.cpp \
    tools/cryptopp/include/lea_simd.cpp \
    tools/cryptopp/include/luc.cpp \
    tools/cryptopp/include/mars.cpp \
    tools/cryptopp/include/marss.cpp \
    tools/cryptopp/include/md2.cpp \
    tools/cryptopp/include/md4.cpp \
    tools/cryptopp/include/md5.cpp \
    tools/cryptopp/include/misc.cpp \
    tools/cryptopp/include/modes.cpp \
    tools/cryptopp/include/mqueue.cpp \
    tools/cryptopp/include/mqv.cpp \
    tools/cryptopp/include/nbtheory.cpp \
    tools/cryptopp/include/neon_simd.cpp \
    tools/cryptopp/include/oaep.cpp \
    tools/cryptopp/include/osrng.cpp \
    tools/cryptopp/include/padlkrng.cpp \
    tools/cryptopp/include/panama.cpp \
    tools/cryptopp/include/pch.cpp \
    tools/cryptopp/include/pkcspad.cpp \
    tools/cryptopp/include/poly1305.cpp \
    tools/cryptopp/include/polynomi.cpp \
    tools/cryptopp/include/ppc_power7.cpp \
    tools/cryptopp/include/ppc_power8.cpp \
    tools/cryptopp/include/ppc_power9.cpp \
    tools/cryptopp/include/ppc_simd.cpp \
    tools/cryptopp/include/pssr.cpp \
    tools/cryptopp/include/pubkey.cpp \
    tools/cryptopp/include/queue.cpp \
    tools/cryptopp/include/rabbit.cpp \
    tools/cryptopp/include/rabin.cpp \
    tools/cryptopp/include/randpool.cpp \
    tools/cryptopp/include/rc2.cpp \
    tools/cryptopp/include/rc5.cpp \
    tools/cryptopp/include/rc6.cpp \
    tools/cryptopp/include/rdrand.cpp \
    tools/cryptopp/include/rdtables.cpp \
    tools/cryptopp/include/regtest1.cpp \
    tools/cryptopp/include/regtest2.cpp \
    tools/cryptopp/include/regtest3.cpp \
    tools/cryptopp/include/regtest4.cpp \
    tools/cryptopp/include/rijndael.cpp \
    tools/cryptopp/include/rijndael_simd.cpp \
    tools/cryptopp/include/ripemd.cpp \
    tools/cryptopp/include/rng.cpp \
    tools/cryptopp/include/rsa.cpp \
    tools/cryptopp/include/rw.cpp \
    tools/cryptopp/include/safer.cpp \
    tools/cryptopp/include/salsa.cpp \
    tools/cryptopp/include/scrypt.cpp \
    tools/cryptopp/include/seal.cpp \
    tools/cryptopp/include/seed.cpp \
    tools/cryptopp/include/serpent.cpp \
    tools/cryptopp/include/sha.cpp \
    tools/cryptopp/include/sha3.cpp \
    tools/cryptopp/include/sha_simd.cpp \
    tools/cryptopp/include/shacal2.cpp \
    tools/cryptopp/include/shacal2_simd.cpp \
    tools/cryptopp/include/shake.cpp \
    tools/cryptopp/include/shark.cpp \
    tools/cryptopp/include/sharkbox.cpp \
    tools/cryptopp/include/simeck.cpp \
    tools/cryptopp/include/simon.cpp \
    tools/cryptopp/include/simon128_simd.cpp \
    tools/cryptopp/include/simple.cpp \
    tools/cryptopp/include/skipjack.cpp \
    tools/cryptopp/include/sm3.cpp \
    tools/cryptopp/include/sm4.cpp \
    tools/cryptopp/include/sm4_simd.cpp \
    tools/cryptopp/include/sosemanuk.cpp \
    tools/cryptopp/include/speck.cpp \
    tools/cryptopp/include/speck128_simd.cpp \
    tools/cryptopp/include/square.cpp \
    tools/cryptopp/include/squaretb.cpp \
    tools/cryptopp/include/sse_simd.cpp \
    tools/cryptopp/include/strciphr.cpp \
    tools/cryptopp/include/tea.cpp \
    tools/cryptopp/include/test.cpp \
    tools/cryptopp/include/tftables.cpp \
    tools/cryptopp/include/threefish.cpp \
    tools/cryptopp/include/tiger.cpp \
    tools/cryptopp/include/tigertab.cpp \
    tools/cryptopp/include/ttmac.cpp \
    tools/cryptopp/include/tweetnacl.cpp \
    tools/cryptopp/include/twofish.cpp \
    tools/cryptopp/include/validat0.cpp \
    tools/cryptopp/include/validat1.cpp \
    tools/cryptopp/include/validat10.cpp \
    tools/cryptopp/include/validat2.cpp \
    tools/cryptopp/include/validat3.cpp \
    tools/cryptopp/include/validat4.cpp \
    tools/cryptopp/include/validat5.cpp \
    tools/cryptopp/include/validat6.cpp \
    tools/cryptopp/include/validat7.cpp \
    tools/cryptopp/include/validat8.cpp \
    tools/cryptopp/include/validat9.cpp \
    tools/cryptopp/include/vmac.cpp \
    tools/cryptopp/include/wake.cpp \
    tools/cryptopp/include/whrlpool.cpp \
    tools/cryptopp/include/xed25519.cpp \
    tools/cryptopp/include/xtr.cpp \
    tools/cryptopp/include/xtrcrypt.cpp \
    tools/cryptopp/include/xts.cpp \
    tools/cryptopp/include/zdeflate.cpp \
    tools/cryptopp/include/zinflate.cpp \
    tools/cryptopp/include/zlib.cpp

HEADERS += \
    cryptopputil.h \
        calibration.h \
    camera.h \
    cam_neican.h \
    nameimg.h \
    setboard.h \
    camera_neican_help.h \
    newcamerproject.h \
    savecamerresult.h \
    external_camera.h\
    camerawithlidar.h \
    lidarwithlidar.h \
    graphicsview.h \
    imagebox.h \
    result_verify.h\
    tools/cryptopp/include/3way.h \
    tools/cryptopp/include/adler32.h \
    tools/cryptopp/include/adv_simd.h \
    tools/cryptopp/include/aes.h \
    tools/cryptopp/include/aes_armv4.h \
    tools/cryptopp/include/algebra.h \
    tools/cryptopp/include/algparam.h \
    tools/cryptopp/include/allocate.h \
    tools/cryptopp/include/arc4.h \
    tools/cryptopp/include/argnames.h \
    tools/cryptopp/include/aria.h \
    tools/cryptopp/include/arm_simd.h \
    tools/cryptopp/include/asn.h \
    tools/cryptopp/include/authenc.h \
    tools/cryptopp/include/base32.h \
    tools/cryptopp/include/base64.h \
    tools/cryptopp/include/basecode.h \
    tools/cryptopp/include/bench.h \
    tools/cryptopp/include/blake2.h \
    tools/cryptopp/include/blowfish.h \
    tools/cryptopp/include/blumshub.h \
    tools/cryptopp/include/camellia.h \
    tools/cryptopp/include/cast.h \
    tools/cryptopp/include/cbcmac.h \
    tools/cryptopp/include/ccm.h \
    tools/cryptopp/include/chacha.h \
    tools/cryptopp/include/chachapoly.h \
    tools/cryptopp/include/cham.h \
    tools/cryptopp/include/channels.h \
    tools/cryptopp/include/cmac.h \
    tools/cryptopp/include/config.h \
    tools/cryptopp/include/config_align.h \
    tools/cryptopp/include/config_asm.h \
    tools/cryptopp/include/config_cpu.h \
    tools/cryptopp/include/config_cxx.h \
    tools/cryptopp/include/config_dll.h \
    tools/cryptopp/include/config_int.h \
    tools/cryptopp/include/config_misc.h \
    tools/cryptopp/include/config_ns.h \
    tools/cryptopp/include/config_os.h \
    tools/cryptopp/include/config_ver.h \
    tools/cryptopp/include/cpu.h \
    tools/cryptopp/include/crc.h \
    tools/cryptopp/include/cryptlib.h \
    tools/cryptopp/include/darn.h \
    tools/cryptopp/include/default.h \
    tools/cryptopp/include/des.h \
    tools/cryptopp/include/dh.h \
    tools/cryptopp/include/dh2.h \
    tools/cryptopp/include/dll.h \
    tools/cryptopp/include/dmac.h \
    tools/cryptopp/include/donna.h \
    tools/cryptopp/include/donna_32.h \
    tools/cryptopp/include/donna_64.h \
    tools/cryptopp/include/donna_sse.h \
    tools/cryptopp/include/drbg.h \
    tools/cryptopp/include/dsa.h \
    tools/cryptopp/include/eax.h \
    tools/cryptopp/include/ec2n.h \
    tools/cryptopp/include/eccrypto.h \
    tools/cryptopp/include/ecp.h \
    tools/cryptopp/include/ecpoint.h \
    tools/cryptopp/include/elgamal.h \
    tools/cryptopp/include/emsa2.h \
    tools/cryptopp/include/eprecomp.h \
    tools/cryptopp/include/esign.h \
    tools/cryptopp/include/factory.h \
    tools/cryptopp/include/fhmqv.h \
    tools/cryptopp/include/files.h \
    tools/cryptopp/include/filters.h \
    tools/cryptopp/include/fips140.h \
    tools/cryptopp/include/fltrimpl.h \
    tools/cryptopp/include/gcm.h \
    tools/cryptopp/include/gf256.h \
    tools/cryptopp/include/gf2_32.h \
    tools/cryptopp/include/gf2n.h \
    tools/cryptopp/include/gfpcrypt.h \
    tools/cryptopp/include/gost.h \
    tools/cryptopp/include/gzip.h \
    tools/cryptopp/include/hashfwd.h \
    tools/cryptopp/include/hc128.h \
    tools/cryptopp/include/hc256.h \
    tools/cryptopp/include/hex.h \
    tools/cryptopp/include/hight.h \
    tools/cryptopp/include/hkdf.h \
    tools/cryptopp/include/hmac.h \
    tools/cryptopp/include/hmqv.h \
    tools/cryptopp/include/hrtimer.h \
    tools/cryptopp/include/ida.h \
    tools/cryptopp/include/idea.h \
    tools/cryptopp/include/integer.h \
    tools/cryptopp/include/iterhash.h \
    tools/cryptopp/include/kalyna.h \
    tools/cryptopp/include/keccak.h \
    tools/cryptopp/include/lea.h \
    tools/cryptopp/include/lubyrack.h \
    tools/cryptopp/include/luc.h \
    tools/cryptopp/include/mars.h \
    tools/cryptopp/include/md2.h \
    tools/cryptopp/include/md4.h \
    tools/cryptopp/include/md5.h \
    tools/cryptopp/include/mdc.h \
    tools/cryptopp/include/mersenne.h \
    tools/cryptopp/include/misc.h \
    tools/cryptopp/include/modarith.h \
    tools/cryptopp/include/modes.h \
    tools/cryptopp/include/modexppc.h \
    tools/cryptopp/include/mqueue.h \
    tools/cryptopp/include/mqv.h \
    tools/cryptopp/include/naclite.h \
    tools/cryptopp/include/nbtheory.h \
    tools/cryptopp/include/nr.h \
    tools/cryptopp/include/oaep.h \
    tools/cryptopp/include/oids.h \
    tools/cryptopp/include/osrng.h \
    tools/cryptopp/include/ossig.h \
    tools/cryptopp/include/padlkrng.h \
    tools/cryptopp/include/panama.h \
    tools/cryptopp/include/pch.h \
    tools/cryptopp/include/pkcspad.h \
    tools/cryptopp/include/poly1305.h \
    tools/cryptopp/include/polynomi.h \
    tools/cryptopp/include/ppc_simd.h \
    tools/cryptopp/include/pssr.h \
    tools/cryptopp/include/pubkey.h \
    tools/cryptopp/include/pwdbased.h \
    tools/cryptopp/include/queue.h \
    tools/cryptopp/include/rabbit.h \
    tools/cryptopp/include/rabin.h \
    tools/cryptopp/include/randpool.h \
    tools/cryptopp/include/rc2.h \
    tools/cryptopp/include/rc5.h \
    tools/cryptopp/include/rc6.h \
    tools/cryptopp/include/rdrand.h \
    tools/cryptopp/include/resource.h \
    tools/cryptopp/include/rijndael.h \
    tools/cryptopp/include/ripemd.h \
    tools/cryptopp/include/rng.h \
    tools/cryptopp/include/rsa.h \
    tools/cryptopp/include/rw.h \
    tools/cryptopp/include/safer.h \
    tools/cryptopp/include/salsa.h \
    tools/cryptopp/include/scrypt.h \
    tools/cryptopp/include/seal.h \
    tools/cryptopp/include/secblock.h \
    tools/cryptopp/include/secblockfwd.h \
    tools/cryptopp/include/seckey.h \
    tools/cryptopp/include/seed.h \
    tools/cryptopp/include/serpent.h \
    tools/cryptopp/include/serpentp.h \
    tools/cryptopp/include/sha.h \
    tools/cryptopp/include/sha1_armv4.h \
    tools/cryptopp/include/sha256_armv4.h \
    tools/cryptopp/include/sha3.h \
    tools/cryptopp/include/sha512_armv4.h \
    tools/cryptopp/include/shacal2.h \
    tools/cryptopp/include/shake.h \
    tools/cryptopp/include/shark.h \
    tools/cryptopp/include/simeck.h \
    tools/cryptopp/include/simon.h \
    tools/cryptopp/include/simple.h \
    tools/cryptopp/include/siphash.h \
    tools/cryptopp/include/skipjack.h \
    tools/cryptopp/include/sm3.h \
    tools/cryptopp/include/sm4.h \
    tools/cryptopp/include/smartptr.h \
    tools/cryptopp/include/sosemanuk.h \
    tools/cryptopp/include/speck.h \
    tools/cryptopp/include/square.h \
    tools/cryptopp/include/stdcpp.h \
    tools/cryptopp/include/strciphr.h \
    tools/cryptopp/include/tea.h \
    tools/cryptopp/include/threefish.h \
    tools/cryptopp/include/tiger.h \
    tools/cryptopp/include/trap.h \
    tools/cryptopp/include/trunhash.h \
    tools/cryptopp/include/ttmac.h \
    tools/cryptopp/include/tweetnacl.h \
    tools/cryptopp/include/twofish.h \
    tools/cryptopp/include/validate.h \
    tools/cryptopp/include/vmac.h \
    tools/cryptopp/include/wake.h \
    tools/cryptopp/include/whrlpool.h \
    tools/cryptopp/include/words.h \
    tools/cryptopp/include/xed25519.h \
    tools/cryptopp/include/xtr.h \
    tools/cryptopp/include/xtrcrypt.h \
    tools/cryptopp/include/xts.h \
    tools/cryptopp/include/zdeflate.h \
    tools/cryptopp/include/zinflate.h \
    tools/cryptopp/include/zlib.h

FORMS += \
        calibration.ui \
    camera.ui \
    nameimg.ui \
    setboard.ui \
    camera_neican_help.ui \
    newcamerproject.ui \
    savecamerresult.ui \
    external_camera.ui \
    camerawithlidar.ui \
    lidarwithlidar.ui

INCLUDEPATH += /usr/local/include \
               /usr/local/include/opencv4 \
               /usr/local/include/opencv4/opencv2

LIBS += /usr/local/lib/libopencv_*

#Eigen
INCLUDEPATH += /usr/include/eigen3

#Vtk
INCLUDEPATH += /usr/local/include/vtk-7.1
LIBS += /usr/local/lib/libvtk*.so

#Boost
INCLUDEPATH += /usr/include/boost
LIBS += /usr/lib/x86_64-linux-gnu/libboost_*.so

INCLUDEPATH += /usr/local/include/pcl-1.8
LIBS += /usr/local/lib/libpcl_*.so

##
#INCLUDEPATH += /usr/local/include/liblas
#LIBS += /usr/local/lib/liblas*.so

#glog
INCLUDEPATH += /usr/include/glog
#g2o
INCLUDEPATH += /usr/local/include/g2o
LIBS += /usr/local/lib/libg2o_*.so
#sophus
INCLUDEPATH +=/usr/local/include/sophus
# cryptopp
INCLUDEPATH += tools/cryptopp/include
