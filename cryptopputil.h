#ifndef CRYPTOPPUTIL_H
#define CRYPTOPPUTIL_H

#define CRYPTOPP_DEFAULT_NO_DLL
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include "dll.h"
#include "cryptlib.h"
#include "aes.h"
#include "filters.h"
#include "md5.h"
#include "ripemd.h"
#include "rng.h"
#include "gzip.h"
#include "default.h"
#include "randpool.h"
#include "ida.h"
#include "base64.h"
#include "factory.h"
#include "whrlpool.h"
#include "tiger.h"
#include "smartptr.h"
#include "pkcspad.h"
#include "stdcpp.h"
#include "osrng.h"
#include "ossig.h"
#include "trap.h"

#include "validate.h"
#include "bench.h"

#include <iostream>
#include <sstream>
#include <locale>
#include <cstdlib>
#include <ctime>

#ifdef CRYPTOPP_WIN32_AVAILABLE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#if defined(CRYPTOPP_UNIX_AVAILABLE) || defined(CRYPTOPP_BSD_AVAILABLE)
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define UNIX_PATH_FAMILY 1
#endif

#if defined(CRYPTOPP_OSX_AVAILABLE)
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <mach-o/dyld.h>
#define UNIX_PATH_FAMILY 1
#endif

#if (_MSC_VER >= 1000)
#include <crtdbg.h>		// for the debug heap
#endif

#if defined(__MWERKS__) && defined(macintosh)
#include <console.h>
#endif

#ifdef _OPENMP
# include <omp.h>
#endif

#ifdef __BORLANDC__
#pragma comment(lib, "cryptlib_bds.lib")
#endif

// Aggressive stack checking with VS2005 SP1 and above.
#if (_MSC_FULL_VER >= 140050727)
# pragma strict_gs_check (on)
#endif

NAMESPACE_BEGIN(CryptoPP)
class CryptoppAPI
{
public:
    std::string EncryptString(const char *instr, const char *passPhrase)
    {
        std::string outstr;

        DefaultEncryptorWithMAC encryptor(passPhrase, new HexEncoder(new StringSink(outstr)));
        encryptor.Put((byte *)instr, strlen(instr));
        encryptor.MessageEnd();

        return outstr;
    }

    std::string DecryptString(const char *instr, const char *passPhrase)
    {
        std::string outstr;

        HexDecoder decryptor(new DefaultDecryptorWithMAC(passPhrase, new StringSink(outstr)));
        decryptor.Put((byte *)instr, strlen(instr));
        decryptor.MessageEnd();

        return outstr;
    }


};
NAMESPACE_END

#include <QString>
class CryptoPPUtil
{
public:
    static QString EncryptString(const QString& instr, const QString& passPhrase)
    {
        return QString::fromStdString(crypto.EncryptString(instr.toUtf8(), passPhrase.toUtf8()));
    }

    static QString DecryptString(const QString& instr, const QString& passPhrase)
    {
        try { // 不一定能解密成功，加密后文本修改或者秘钥错误
            return QString::fromStdString(crypto.DecryptString(instr.toUtf8(), passPhrase.toUtf8()));
        } catch (...) {
            return QString();
        }
    }

private:
    static inline CryptoPP::CryptoppAPI crypto;
};

#endif // CRYPTOPPUTIL_H
