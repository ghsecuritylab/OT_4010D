
#ifndef _ANYTRANS_H_
#define _ANYTRANS_H_

#include "unicode/utypes.h"

#if !UCONFIG_NO_TRANSLITERATION

#include "unicode/translit.h"
#include "unicode/uscript.h"
#include "uhash.h"

U_NAMESPACE_BEGIN

class AnyTransliterator : public Transliterator {

    /**
     * Cache mapping UScriptCode values to Transliterator*.
     */
    UHashtable* cache;

    /**
     * The target or target/variant string.
     */
    UnicodeString target;

    /**
     * The target script code.  Never USCRIPT_INVALID_CODE.
     */
    UScriptCode targetScript;

public:

    /**
     * Destructor.
     */
    virtual ~AnyTransliterator();

    /**
     * Copy constructor.
     */
    AnyTransliterator(const AnyTransliterator&);

    /**
     * Transliterator API.
     */
    virtual Transliterator* clone() const;

    /**
     * Implements {@link Transliterator#handleTransliterate}.
     */
    virtual void handleTransliterate(Replaceable& text, UTransPosition& index,
                                     UBool incremental) const;

    /**
     * ICU "poor man's RTTI", returns a UClassID for the actual class.
     */
    virtual UClassID getDynamicClassID() const;

    /**
     * ICU "poor man's RTTI", returns a UClassID for this class.
     */
    U_I18N_API static UClassID U_EXPORT2 getStaticClassID();

private:

    /**
     * Private constructor
     * @param id the ID of the form S-T or S-T/V, where T is theTarget
     * and V is theVariant.  Must not be empty.
     * @param theTarget the target name.  Must not be empty, and must
     * name a script corresponding to theTargetScript.
     * @param theVariant the variant name, or the empty string if
     * there is no variant
     * @param theTargetScript the script code corresponding to
     * theTarget.
     * @param ec error code, fails if the internal hashtable cannot be
     * allocated
     */
    AnyTransliterator(const UnicodeString& id,
                      const UnicodeString& theTarget,
                      const UnicodeString& theVariant,
                      UScriptCode theTargetScript,
                      UErrorCode& ec);

    /**
     * Returns a transliterator from the given source to our target or
     * target/variant.  Returns NULL if the source is the same as our
     * target script, or if the source is USCRIPT_INVALID_CODE.
     * Caches the result and returns the same transliterator the next
     * time.  The caller does NOT own the result and must not delete
     * it.
     */
    Transliterator* getTransliterator(UScriptCode source) const;

    /**
     * Registers standard transliterators with the system.  Called by
     * Transliterator during initialization.
     */
    static void registerIDs();

    friend class Transliterator; // for registerIDs()
};

U_NAMESPACE_END

#endif /* #if !UCONFIG_NO_TRANSLITERATION */

#endif
