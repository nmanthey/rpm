#ifndef	H_RPMGI
#define	H_RPMGI

/** \ingroup rpmio
 * \file rpmio/rpmgi.h
 */

#include <rpmlib.h>
#include <rpmts.h>
#include <fts.h>
#include <argv.h>

/**
 */
/*@-exportlocal@*/
/*@unchecked@*/
extern int _rpmgi_debug;
/*@=exportlocal@*/

/**
 */
typedef enum rpmgiTag_e {
    RPMGI_RPMDB		= RPMDBI_PACKAGES,
    RPMGI_HDLIST	= 6,	/* XXX next after RPMDBI_AVAILABLE */
    RPMGI_ARGLIST	= 7,
    RPMGI_FTSWALK	= 8
} rpmgiTag;

#if defined(_RPMGI_INTERNAL)
/** \ingroup rpmio
 */
struct rpmgi_s {
/*@refcounted@*/
    rpmts ts;
    int tag;
    int i;
    const char * queryFormat;

/*@relnull@*/
    rpmdbMatchIterator mi;

/*@refcounted@*/
    FD_t fd;

    ARGV_t argv;
    int argc;

    int ftsOpts;
    FTS * ftsp;
    FTSENT * fts;

/*@refs@*/
    int nrefs;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Unreference a generalized iterator instance.
 * @param gi		generalized iterator
 * @param msg
 * @return		NULL always
 */
/*@unused@*/ /*@null@*/
rpmgi rpmgiUnlink (/*@killref@*/ /*@only@*/ /*@null@*/ rpmgi gi,
		/*@null@*/ const char * msg)
	/*@modifies gi @*/;

/** @todo Remove debugging entry from the ABI. */
/*@-exportlocal@*/
/*@null@*/
rpmgi XrpmgiUnlink (/*@killref@*/ /*@only@*/ /*@null@*/ rpmgi gi,
		/*@null@*/ const char * msg, const char * fn, unsigned ln)
	/*@modifies gi @*/;
/*@=exportlocal@*/
#define	rpmgiUnlink(_gi, _msg)	XrpmgiUnlink(_gi, _msg, __FILE__, __LINE__)

/**
 * Reference a generalized iterator instance.
 * @param gi		generalized iterator
 * @param msg
 * @return		new generalized iterator reference
 */
/*@unused@*/ /*@newref@*/ /*@null@*/
rpmgi rpmgiLink (/*@null@*/ rpmgi gi, /*@null@*/ const char * msg)
	/*@modifies gi @*/;

/** @todo Remove debugging entry from the ABI. */
/*@newref@*/ /*@null@*/
rpmgi XrpmgiLink (/*@null@*/ rpmgi gi, /*@null@*/ const char * msg,
		const char * fn, unsigned ln)
        /*@modifies gi @*/;
#define	rpmgiLink(_gi, _msg)	XrpmgiLink(_gi, _msg, __FILE__, __LINE__)

/** Destroy a generalized iterator.
 * @param gi		generalized iterator
 * @return		NULL always
 */
/*@null@*/
rpmgi rpmgiFree(/*@killref@*/ /*@only@*/ /*@null@*/ rpmgi gi)
	/*@globals rpmGlobalMacroContext, h_errno, internalState @*/
        /*@modifies gi, rpmGlobalMacroContext, h_errno, internalState @*/;

/** Create a generalized iterator.
 * @param argv		iterator argv array
 * @param flags		iterator flags
 * @return		new general iterator
 */
/*@null@*/
rpmgi rpmgiNew(rpmts ts, int tag, void *const keyp, size_t keylen)
	/*@globals rpmGlobalMacroContext, h_errno, internalState @*/
	/*@modifies ts, rpmGlobalMacroContext, h_errno, internalState @*/;

/** Return next iteration element.
 * @param gi		generalized iterator
 * @returns		next element
 */
/*@observer@*/
const char * rpmgiNext(/*@null@*/ rpmgi gi)
	/*@globals rpmGlobalMacroContext, h_errno, internalState @*/
        /*@modifies gi, rpmGlobalMacroContext, h_errno, internalState @*/;

int rpmgiSetQueryFormat(rpmgi gi, const char * queryFormat)
	/*@modifies gi @*/;

#ifdef __cplusplus
}
#endif

#endif	/* H_RPMGI */
