#ifndef DEBUG_UTILS_H
#define DEBUG_UTILS_H

#ifdef __GNUC__

  #include <csignal>

  #ifdef DEBUG
    #define DEBUG_PAUSE(reason) (std::raise (SIGTRAP));
  #else
    #define DEBUG_PAUSE(reason)
  #endif

#else

  #ifdef __WIN32__
    #ifdef DEBUG
      #define DEBUG_PAUSE(reason) (__debugbreak ());
    #else
      #define DEBUG_PAUSE(reason)
    #endif

  #else

    #define DEBUG_PAUSE(reason)

  #endif //__WIN32__

#endif //__GNUC>__

#define DEBUG_ASSERT(assertion) (if (!(assertion)) DEBUG_PAUSE (""););
#define ASSERT_RETURN(assertion, retval) if (!(assertion)) {DEBUG_PAUSE (""); return retval;}

template<typename... Args>
void FIX_UNUSED (Args &&...) {}
#endif // DEBUG_UTILS_H
