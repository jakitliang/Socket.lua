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
        { .name = "EPERM", .value = EPERM },
#endif
#ifdef ENOENT
        { .name = "ENOENT", .value = ENOENT },
#endif
#ifdef ESRCH
        { .name = "ESRCH", .value = ESRCH },
#endif
#ifdef EINTR
        { .name = "EINTR", .value = EINTR },
#endif
#ifdef EIO
        { .name = "EIO", .value = EIO },
#endif
#ifdef ENXIO
        { .name = "ENXIO", .value = ENXIO },
#endif
#ifdef E2BIG
        { .name = "E2BIG", .value = E2BIG },
#endif
#ifdef ENOEXEC
        { .name = "ENOEXEC", .value = ENOEXEC },
#endif
#ifdef EBADF
        { .name = "EBADF", .value = EBADF },
#endif
#ifdef ECHILD
        { .name = "ECHILD", .value = ECHILD },
#endif
#ifdef EDEADLK
        { .name = "EDEADLK", .value = EDEADLK },
#endif
#ifdef ENOMEM
        { .name = "ENOMEM", .value = ENOMEM },
#endif
#ifdef EACCES
        { .name = "EACCES", .value = EACCES },
#endif
#ifdef EFAULT
        { .name = "EFAULT", .value = EFAULT },
#endif
#ifdef ENOTBLK
        { .name = "ENOTBLK", .value = ENOTBLK },
#endif
#ifdef EBUSY
        { .name = "EBUSY", .value = EBUSY },
#endif
#ifdef EEXIST
        { .name = "EEXIST", .value = EEXIST },
#endif
#ifdef EXDEV
        { .name = "EXDEV", .value = EXDEV },
#endif
#ifdef ENODEV
        { .name = "ENODEV", .value = ENODEV },
#endif
#ifdef ENOTDIR
        { .name = "ENOTDIR", .value = ENOTDIR },
#endif
#ifdef EISDIR
        { .name = "EISDIR", .value = EISDIR },
#endif
#ifdef EINVAL
        { .name = "EINVAL", .value = EINVAL },
#endif
#ifdef ENFILE
        { .name = "ENFILE", .value = ENFILE },
#endif
#ifdef EMFILE
        { .name = "EMFILE", .value = EMFILE },
#endif
#ifdef ENOTTY
        { .name = "ENOTTY", .value = ENOTTY },
#endif
#ifdef ETXTBSY
        { .name = "ETXTBSY", .value = ETXTBSY },
#endif
#ifdef EFBIG
        { .name = "EFBIG", .value = EFBIG },
#endif
#ifdef ENOSPC
        { .name = "ENOSPC", .value = ENOSPC },
#endif
#ifdef ESPIPE
        { .name = "ESPIPE", .value = ESPIPE },
#endif
#ifdef EROFS
        { .name = "EROFS", .value = EROFS },
#endif
#ifdef EMLINK
        { .name = "EMLINK", .value = EMLINK },
#endif
#ifdef EPIPE
        { .name = "EPIPE", .value = EPIPE },
#endif
#ifdef EDOM
        { .name = "EDOM", .value = EDOM },
#endif
#ifdef ERANGE
        { .name = "ERANGE", .value = ERANGE },
#endif
#ifdef EAGAIN
        { .name = "EAGAIN", .value = EAGAIN },
#endif
#ifdef EWOULDBLOCK
        { .name = "EWOULDBLOCK", .value = EWOULDBLOCK },
#endif
#ifdef EINPROGRESS
        { .name = "EINPROGRESS", .value = EINPROGRESS },
#endif
#ifdef EALREADY
        { .name = "EALREADY", .value = EALREADY },
#endif
#ifdef ENOTSOCK
        { .name = "ENOTSOCK", .value = ENOTSOCK },
#endif
#ifdef EDESTADDRREQ
        { .name = "EDESTADDRREQ", .value = EDESTADDRREQ },
#endif
#ifdef EMSGSIZE
        { .name = "EMSGSIZE", .value = EMSGSIZE },
#endif
#ifdef EPROTOTYPE
        { .name = "EPROTOTYPE", .value = EPROTOTYPE },
#endif
#ifdef ENOPROTOOPT
        { .name = "ENOPROTOOPT", .value = ENOPROTOOPT },
#endif
#ifdef EPROTONOSUPPORT
        { .name = "EPROTONOSUPPORT", .value = EPROTONOSUPPORT },
#endif
#ifdef ESOCKTNOSUPPORT
        { .name = "ESOCKTNOSUPPORT", .value = ESOCKTNOSUPPORT },
#endif
#ifdef ENOTSUP
        { .name = "ENOTSUP", .value = ENOTSUP },
#endif
#ifdef EOPNOTSUPP
        { .name = "EOPNOTSUPP", .value = EOPNOTSUPP },
#endif
#ifdef EPFNOSUPPORT
        { .name = "EPFNOSUPPORT", .value = EPFNOSUPPORT },
#endif
#ifdef EAFNOSUPPORT
        { .name = "EAFNOSUPPORT", .value = EAFNOSUPPORT },
#endif
#ifdef EADDRINUSE
        { .name = "EADDRINUSE", .value = EADDRINUSE },
#endif
#ifdef EADDRNOTAVAIL
        { .name = "EADDRNOTAVAIL", .value = EADDRNOTAVAIL },
#endif
#ifdef ENETDOWN
        { .name = "ENETDOWN", .value = ENETDOWN },
#endif
#ifdef ENETUNREACH
        { .name = "ENETUNREACH", .value = ENETUNREACH },
#endif
#ifdef ENETRESET
        { .name = "ENETRESET", .value = ENETRESET },
#endif
#ifdef ECONNABORTED
        { .name = "ECONNABORTED", .value = ECONNABORTED },
#endif
#ifdef ECONNRESET
        { .name = "ECONNRESET", .value = ECONNRESET },
#endif
#ifdef ENOBUFS
        { .name = "ENOBUFS", .value = ENOBUFS },
#endif
#ifdef EISCONN
        { .name = "EISCONN", .value = EISCONN },
#endif
#ifdef ENOTCONN
        { .name = "ENOTCONN", .value = ENOTCONN },
#endif
#ifdef ESHUTDOWN
        { .name = "ESHUTDOWN", .value = ESHUTDOWN },
#endif
#ifdef ETOOMANYREFS
        { .name = "ETOOMANYREFS", .value = ETOOMANYREFS },
#endif
#ifdef ETIMEDOUT
        { .name = "ETIMEDOUT", .value = ETIMEDOUT },
#endif
#ifdef ECONNREFUSED
        { .name = "ECONNREFUSED", .value = ECONNREFUSED },
#endif
#ifdef ELOOP
        { .name = "ELOOP", .value = ELOOP },
#endif
#ifdef ENAMETOOLONG
        { .name = "ENAMETOOLONG", .value = ENAMETOOLONG },
#endif
#ifdef EHOSTDOWN
        { .name = "EHOSTDOWN", .value = EHOSTDOWN },
#endif
#ifdef EHOSTUNREACH
        { .name = "EHOSTUNREACH", .value = EHOSTUNREACH },
#endif
#ifdef ENOTEMPTY
        { .name = "ENOTEMPTY", .value = ENOTEMPTY },
#endif
#ifdef EPROCLIM
        { .name = "EPROCLIM", .value = EPROCLIM },
#endif
#ifdef EUSERS
        { .name = "EUSERS", .value = EUSERS },
#endif
#ifdef EDQUOT
        { .name = "EDQUOT", .value = EDQUOT },
#endif
#ifdef ESTALE
        { .name = "ESTALE", .value = ESTALE },
#endif
#ifdef EREMOTE
        { .name = "EREMOTE", .value = EREMOTE },
#endif
#ifdef EBADRPC
        { .name = "EBADRPC", .value = EBADRPC },
#endif
#ifdef ERPCMISMATCH
        { .name = "ERPCMISMATCH", .value = ERPCMISMATCH },
#endif
#ifdef EPROGUNAVAIL
        { .name = "EPROGUNAVAIL", .value = EPROGUNAVAIL },
#endif
#ifdef EPROGMISMATCH
        { .name = "EPROGMISMATCH", .value = EPROGMISMATCH },
#endif
#ifdef EPROCUNAVAIL
        { .name = "EPROCUNAVAIL", .value = EPROCUNAVAIL },
#endif
#ifdef ENOLCK
        { .name = "ENOLCK", .value = ENOLCK },
#endif
#ifdef ENOSYS
        { .name = "ENOSYS", .value = ENOSYS },
#endif
#ifdef EFTYPE
        { .name = "EFTYPE", .value = EFTYPE },
#endif
#ifdef EAUTH
        { .name = "EAUTH", .value = EAUTH },
#endif
#ifdef ENEEDAUTH
        { .name = "ENEEDAUTH", .value = ENEEDAUTH },
#endif
#ifdef EPWROFF
        { .name = "EPWROFF", .value = EPWROFF },
#endif
#ifdef EDEVERR
        { .name = "EDEVERR", .value = EDEVERR },
#endif
#ifdef EOVERFLOW
        { .name = "EOVERFLOW", .value = EOVERFLOW },
#endif
#ifdef EBADEXEC
        { .name = "EBADEXEC", .value = EBADEXEC },
#endif
#ifdef EBADARCH
        { .name = "EBADARCH", .value = EBADARCH },
#endif
#ifdef ESHLIBVERS
        { .name = "ESHLIBVERS", .value = ESHLIBVERS },
#endif
#ifdef EBADMACHO
        { .name = "EBADMACHO", .value = EBADMACHO },
#endif
#ifdef ECANCELED
        { .name = "ECANCELED", .value = ECANCELED },
#endif
#ifdef EIDRM
        { .name = "EIDRM", .value = EIDRM },
#endif
#ifdef ENOMSG
        { .name = "ENOMSG", .value = ENOMSG },
#endif
#ifdef EILSEQ
        { .name = "EILSEQ", .value = EILSEQ },
#endif
#ifdef ENOATTR
        { .name = "ENOATTR", .value = ENOATTR },
#endif
#ifdef EBADMSG
        { .name = "EBADMSG", .value = EBADMSG },
#endif
#ifdef EMULTIHOP
        { .name = "EMULTIHOP", .value = EMULTIHOP },
#endif
#ifdef ENODATA
        { .name = "ENODATA", .value = ENODATA },
#endif
#ifdef ENOLINK
        { .name = "ENOLINK", .value = ENOLINK },
#endif
#ifdef ENOSR
        { .name = "ENOSR", .value = ENOSR },
#endif
#ifdef ENOSTR
        { .name = "ENOSTR", .value = ENOSTR },
#endif
#ifdef EPROTO
        { .name = "EPROTO", .value = EPROTO },
#endif
#ifdef ETIME
        { .name = "ETIME", .value = ETIME },
#endif
#ifdef EOPNOTSUPP
        { .name = "EOPNOTSUPP", .value = EOPNOTSUPP },
#endif
#ifdef ENOPOLICY
        { .name = "ENOPOLICY", .value = ENOPOLICY },
#endif
#ifdef ENOTRECOVERABLE
        { .name = "ENOTRECOVERABLE", .value = ENOTRECOVERABLE },
#endif
#ifdef EOWNERDEAD
        { .name = "EOWNERDEAD", .value = EOWNERDEAD },
#endif
#ifdef EQFULL
        { .name = "EQFULL", .value = EQFULL },
#endif
#ifdef ELAST
        { .name = "ELAST", .value = ELAST },
#endif
#ifdef _WIN32
#define ESOCKTNOSUPPORT 44
        { .name = "ESOCKTNOSUPPORT", .value = ESOCKTNOSUPPORT },
#define EPFNOSUPPORT 46
        { .name = "EPFNOSUPPORT", .value = EPFNOSUPPORT },
#define ESHUTDOWN 58
        { .name = "ESHUTDOWN", .value = ESHUTDOWN },
#define ETOOMANYREFS 59
        { .name = "ETOOMANYREFS", .value = ETOOMANYREFS },
#define EHOSTDOWN 64
        { .name = "EHOSTDOWN", .value = EHOSTDOWN },
#define EPROCLIM 67
        { .name = "EPROCLIM", .value = EPROCLIM },
#define EUSERS 68
        { .name = "EUSERS", .value = EUSERS },
#define EDQUOT 69
        { .name = "EDQUOT", .value = EDQUOT },
#define ESTALE 70
        { .name = "ESTALE", .value = ESTALE },
#define EREMOTE 71
        { .name = "EREMOTE", .value = EREMOTE },
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
