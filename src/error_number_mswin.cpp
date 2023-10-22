// Socket.lua
// Connect to the world!
// @module 'Socket.errno'
// @author Jakit Liang 泊凛
// @date 2023-10-01
// @license MIT

#include "error_number.h"
#include <cerrno>
#include <map>
#ifdef _WIN32
#include <winsock.h>
#endif

ErrorNumber errorNumber[] = {
#ifdef EPERM
        { "EPERM", EPERM },
#endif
#ifdef ENOENT
        { "ENOENT", ENOENT },
#endif
#ifdef ESRCH
        { "ESRCH", ESRCH },
#endif
#ifdef EINTR
        { "EINTR", EINTR },
#endif
#ifdef EIO
        { "EIO", EIO },
#endif
#ifdef ENXIO
        { "ENXIO", ENXIO },
#endif
#ifdef E2BIG
        { "E2BIG", E2BIG },
#endif
#ifdef ENOEXEC
        { "ENOEXEC", ENOEXEC },
#endif
#ifdef EBADF
        { "EBADF", EBADF },
#endif
#ifdef ECHILD
        { "ECHILD", ECHILD },
#endif
#ifdef EDEADLK
        { "EDEADLK", EDEADLK },
#endif
#ifdef ENOMEM
        { "ENOMEM", ENOMEM },
#endif
#ifdef EACCES
        { "EACCES", EACCES },
#endif
#ifdef EFAULT
        { "EFAULT", EFAULT },
#endif
#ifdef ENOTBLK
        { "ENOTBLK", ENOTBLK },
#endif
#ifdef EBUSY
        { "EBUSY", EBUSY },
#endif
#ifdef EEXIST
        { "EEXIST", EEXIST },
#endif
#ifdef EXDEV
        { "EXDEV", EXDEV },
#endif
#ifdef ENODEV
        { "ENODEV", ENODEV },
#endif
#ifdef ENOTDIR
        { "ENOTDIR", ENOTDIR },
#endif
#ifdef EISDIR
        { "EISDIR", EISDIR },
#endif
#ifdef EINVAL
        { "EINVAL", EINVAL },
#endif
#ifdef ENFILE
        { "ENFILE", ENFILE },
#endif
#ifdef EMFILE
        { "EMFILE", EMFILE },
#endif
#ifdef ENOTTY
        { "ENOTTY", ENOTTY },
#endif
#ifdef ETXTBSY
        { "ETXTBSY", ETXTBSY },
#endif
#ifdef EFBIG
        { "EFBIG", EFBIG },
#endif
#ifdef ENOSPC
        { "ENOSPC", ENOSPC },
#endif
#ifdef ESPIPE
        { "ESPIPE", ESPIPE },
#endif
#ifdef EROFS
        { "EROFS", EROFS },
#endif
#ifdef EMLINK
        { "EMLINK", EMLINK },
#endif
#ifdef EPIPE
        { "EPIPE", EPIPE },
#endif
#ifdef EDOM
        { "EDOM", EDOM },
#endif
#ifdef ERANGE
        { "ERANGE", ERANGE },
#endif
#ifdef EAGAIN
        { "EAGAIN", EAGAIN },
#endif
#ifdef EWOULDBLOCK
        { "EWOULDBLOCK", EWOULDBLOCK },
#endif
#ifdef EINPROGRESS
        { "EINPROGRESS", EINPROGRESS },
#endif
#ifdef EALREADY
        { "EALREADY", EALREADY },
#endif
#ifdef ENOTSOCK
        { "ENOTSOCK", ENOTSOCK },
#endif
#ifdef EDESTADDRREQ
        { "EDESTADDRREQ", EDESTADDRREQ },
#endif
#ifdef EMSGSIZE
        { "EMSGSIZE", EMSGSIZE },
#endif
#ifdef EPROTOTYPE
        { "EPROTOTYPE", EPROTOTYPE },
#endif
#ifdef ENOPROTOOPT
        { "ENOPROTOOPT", ENOPROTOOPT },
#endif
#ifdef EPROTONOSUPPORT
        { "EPROTONOSUPPORT", EPROTONOSUPPORT },
#endif
#ifdef ESOCKTNOSUPPORT
        { "ESOCKTNOSUPPORT", ESOCKTNOSUPPORT },
#endif
#ifdef ENOTSUP
        { "ENOTSUP", ENOTSUP },
#endif
#ifdef EOPNOTSUPP
        { "EOPNOTSUPP", EOPNOTSUPP },
#endif
#ifdef EPFNOSUPPORT
        { "EPFNOSUPPORT", EPFNOSUPPORT },
#endif
#ifdef EAFNOSUPPORT
        { "EAFNOSUPPORT", EAFNOSUPPORT },
#endif
#ifdef EADDRINUSE
        { "EADDRINUSE", EADDRINUSE },
#endif
#ifdef EADDRNOTAVAIL
        { "EADDRNOTAVAIL", EADDRNOTAVAIL },
#endif
#ifdef ENETDOWN
        { "ENETDOWN", ENETDOWN },
#endif
#ifdef ENETUNREACH
        { "ENETUNREACH", ENETUNREACH },
#endif
#ifdef ENETRESET
        { "ENETRESET", ENETRESET },
#endif
#ifdef ECONNABORTED
        { "ECONNABORTED", ECONNABORTED },
#endif
#ifdef ECONNRESET
        { "ECONNRESET", ECONNRESET },
#endif
#ifdef ENOBUFS
        { "ENOBUFS", ENOBUFS },
#endif
#ifdef EISCONN
        { "EISCONN", EISCONN },
#endif
#ifdef ENOTCONN
        { "ENOTCONN", ENOTCONN },
#endif
#ifdef ESHUTDOWN
        { "ESHUTDOWN", ESHUTDOWN },
#endif
#ifdef ETOOMANYREFS
        { "ETOOMANYREFS", ETOOMANYREFS },
#endif
#ifdef ETIMEDOUT
        { "ETIMEDOUT", ETIMEDOUT },
#endif
#ifdef ECONNREFUSED
        { "ECONNREFUSED", ECONNREFUSED },
#endif
#ifdef ELOOP
        { "ELOOP", ELOOP },
#endif
#ifdef ENAMETOOLONG
        { "ENAMETOOLONG", ENAMETOOLONG },
#endif
#ifdef EHOSTDOWN
        { "EHOSTDOWN", EHOSTDOWN },
#endif
#ifdef EHOSTUNREACH
        { "EHOSTUNREACH", EHOSTUNREACH },
#endif
#ifdef ENOTEMPTY
        { "ENOTEMPTY", ENOTEMPTY },
#endif
#ifdef EPROCLIM
        { "EPROCLIM", EPROCLIM },
#endif
#ifdef EUSERS
        { "EUSERS", EUSERS },
#endif
#ifdef EDQUOT
        { "EDQUOT", EDQUOT },
#endif
#ifdef ESTALE
        { "ESTALE", ESTALE },
#endif
#ifdef EREMOTE
        { "EREMOTE", EREMOTE },
#endif
#ifdef EBADRPC
        { "EBADRPC", EBADRPC },
#endif
#ifdef ERPCMISMATCH
        { "ERPCMISMATCH", ERPCMISMATCH },
#endif
#ifdef EPROGUNAVAIL
        { "EPROGUNAVAIL", EPROGUNAVAIL },
#endif
#ifdef EPROGMISMATCH
        { "EPROGMISMATCH", EPROGMISMATCH },
#endif
#ifdef EPROCUNAVAIL
        { "EPROCUNAVAIL", EPROCUNAVAIL },
#endif
#ifdef ENOLCK
        { "ENOLCK", ENOLCK },
#endif
#ifdef ENOSYS
        { "ENOSYS", ENOSYS },
#endif
#ifdef EFTYPE
        { "EFTYPE", EFTYPE },
#endif
#ifdef EAUTH
        { "EAUTH", EAUTH },
#endif
#ifdef ENEEDAUTH
        { "ENEEDAUTH", ENEEDAUTH },
#endif
#ifdef EPWROFF
        { "EPWROFF", EPWROFF },
#endif
#ifdef EDEVERR
        { "EDEVERR", EDEVERR },
#endif
#ifdef EOVERFLOW
        { "EOVERFLOW", EOVERFLOW },
#endif
#ifdef EBADEXEC
        { "EBADEXEC", EBADEXEC },
#endif
#ifdef EBADARCH
        { "EBADARCH", EBADARCH },
#endif
#ifdef ESHLIBVERS
        { "ESHLIBVERS", ESHLIBVERS },
#endif
#ifdef EBADMACHO
        { "EBADMACHO", EBADMACHO },
#endif
#ifdef ECANCELED
        { "ECANCELED", ECANCELED },
#endif
#ifdef EIDRM
        { "EIDRM", EIDRM },
#endif
#ifdef ENOMSG
        { "ENOMSG", ENOMSG },
#endif
#ifdef EILSEQ
        { "EILSEQ", EILSEQ },
#endif
#ifdef ENOATTR
        { "ENOATTR", ENOATTR },
#endif
#ifdef EBADMSG
        { "EBADMSG", EBADMSG },
#endif
#ifdef EMULTIHOP
        { "EMULTIHOP", EMULTIHOP },
#endif
#ifdef ENODATA
        { "ENODATA", ENODATA },
#endif
#ifdef ENOLINK
        { "ENOLINK", ENOLINK },
#endif
#ifdef ENOSR
        { "ENOSR", ENOSR },
#endif
#ifdef ENOSTR
        { "ENOSTR", ENOSTR },
#endif
#ifdef EPROTO
        { "EPROTO", EPROTO },
#endif
#ifdef ETIME
        { "ETIME", ETIME },
#endif
#ifdef EOPNOTSUPP
        { "EOPNOTSUPP", EOPNOTSUPP },
#endif
#ifdef ENOPOLICY
        { "ENOPOLICY", ENOPOLICY },
#endif
#ifdef ENOTRECOVERABLE
        { "ENOTRECOVERABLE", ENOTRECOVERABLE },
#endif
#ifdef EOWNERDEAD
        { "EOWNERDEAD", EOWNERDEAD },
#endif
#ifdef EQFULL
        { "EQFULL", EQFULL },
#endif
#ifdef ELAST
        { "ELAST", ELAST },
#endif
#ifdef _WIN32
#define ESOCKTNOSUPPORT 44
        { "ESOCKTNOSUPPORT", ESOCKTNOSUPPORT },
#define EPFNOSUPPORT 46
        { "EPFNOSUPPORT", EPFNOSUPPORT },
#define ESHUTDOWN 58
        { "ESHUTDOWN", ESHUTDOWN },
#define ETOOMANYREFS 59
        { "ETOOMANYREFS", ETOOMANYREFS },
#define EHOSTDOWN 64
        { "EHOSTDOWN", EHOSTDOWN },
#define EPROCLIM 67
        { "EPROCLIM", EPROCLIM },
#define EUSERS 68
        { "EUSERS", EUSERS },
#define EDQUOT 69
        { "EDQUOT", EDQUOT },
#define ESTALE 70
        { "ESTALE", ESTALE },
#define EREMOTE 71
        { "EREMOTE", EREMOTE },
#endif
};

#ifdef _WIN32
static std::map<int, int> winToPosix = {
        {	WSAEINTR,			EINTR		},
        {	WSAEBADF,			EBADF		},
        {	WSAEACCES,			EACCES		},
        {	WSAEFAULT,			EFAULT		},
        {	WSAEINVAL,			EINVAL		},
        {	WSAEMFILE,			EMFILE		},
        {	WSAEWOULDBLOCK,			EWOULDBLOCK	},
        {	WSAEINPROGRESS,			EINPROGRESS	},
        {	WSAEALREADY,			EALREADY	},
        {	WSAENOTSOCK,			ENOTSOCK	},
        {	WSAEDESTADDRREQ,		EDESTADDRREQ	},
        {	WSAEMSGSIZE,			EMSGSIZE	},
        {	WSAEPROTOTYPE,			EPROTOTYPE	},
        {	WSAENOPROTOOPT,			ENOPROTOOPT	},
        {	WSAEPROTONOSUPPORT,		EPROTONOSUPPORT	},
        {	WSAESOCKTNOSUPPORT,		ESOCKTNOSUPPORT	},
        {	WSAEOPNOTSUPP,			EOPNOTSUPP	},
        {	WSAEPFNOSUPPORT,		EPFNOSUPPORT	},
        {	WSAEAFNOSUPPORT,		EAFNOSUPPORT	},
        {	WSAEADDRINUSE,			EADDRINUSE	},
        {	WSAEADDRNOTAVAIL,		EADDRNOTAVAIL	},
        {	WSAENETDOWN,			ENETDOWN	},
        {	WSAENETUNREACH,			ENETUNREACH	},
        {	WSAENETRESET,			ENETRESET	},
        {	WSAECONNABORTED,		ECONNABORTED	},
        {	WSAECONNRESET,			ECONNRESET	},
        {	WSAENOBUFS,			ENOBUFS		},
        {	WSAEISCONN,			EISCONN		},
        {	WSAENOTCONN,			ENOTCONN	},
        {	WSAESHUTDOWN,			ESHUTDOWN	},
        {	WSAETOOMANYREFS,		ETOOMANYREFS	},
        {	WSAETIMEDOUT,			ETIMEDOUT	},
        {	WSAECONNREFUSED,		ECONNREFUSED	},
        {	WSAELOOP,			ELOOP		},
        {	WSAENAMETOOLONG,		ENAMETOOLONG	},
        {	WSAEHOSTDOWN,			EHOSTDOWN	},
        {	WSAEHOSTUNREACH,		EHOSTUNREACH	},
        {	WSAENOTEMPTY,			ENOTEMPTY	},
        {	WSAEUSERS,			EUSERS		},
        {	WSAEDQUOT,			EDQUOT		},
        {	WSAESTALE,			ESTALE		},
        {	WSAEREMOTE,			EREMOTE		}
};

int ErrorConvert(int n) {
    if (winToPosix.count(n) != 0) {
        return winToPosix[n];
    }

    return n;
}
#endif

int SocketInitError(lua_State *L) {
    lua_newtable(L);
    for (auto & i : errorNumber) {
        lua_pushinteger(L, i.value);
        lua_setfield(L, -2, i.name);
    }
    return 0;
}
