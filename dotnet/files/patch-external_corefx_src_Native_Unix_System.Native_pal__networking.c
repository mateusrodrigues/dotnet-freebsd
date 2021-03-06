--- external/corefx/src/Native/Unix/System.Native/pal_networking.c.orig	2018-06-19 23:42:29 UTC
+++ external/corefx/src/Native/Unix/System.Native/pal_networking.c
@@ -2209,6 +2209,7 @@ static int32_t TryChangeSocketEventRegis
     int8_t writeChanged = (changes & SocketEvents_SA_WRITE) != 0;
 
     struct kevent events[2];
+    int err;
 
     int i = 0;
     if (readChanged)
@@ -2221,6 +2222,20 @@ static int32_t TryChangeSocketEventRegis
                0,
                GetKeventUdata(data));
     }
+#if defined(__FreeBSD__)
+    // Issue: #30698
+    // FreeBSD seems to have some issue when setting read/write events together.
+    // As a workaround use separate kevent() calls
+    if (writeChanged)
+    {
+	    while ((err = kevent(port, events, GetKeventNchanges(i), NULL, 0, NULL)) < 0 && errno == EINTR);
+	    if (err != 0)
+	    {
+		    return SystemNative_ConvertErrorPlatformToPal(errno);
+	    }
+	    i = 0;
+    }
+#endif
 
     if (writeChanged)
     {
@@ -2233,7 +2248,6 @@ static int32_t TryChangeSocketEventRegis
                GetKeventUdata(data));
     }
 
-    int err;
     while ((err = kevent(port, events, GetKeventNchanges(i), NULL, 0, NULL)) < 0 && errno == EINTR);
     return err == 0 ? Error_SUCCESS : SystemNative_ConvertErrorPlatformToPal(errno);
 }
