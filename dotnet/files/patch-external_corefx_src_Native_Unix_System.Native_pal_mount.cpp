--- external/corefx/src/Native/Unix/System.Native/pal_mount.cpp     2018-08-09 12:30:43.660277000 -0300
+++ external/corefx/src/Native/Unix/System.Native/pal_mount.cpp     2018-06-19 20:42:29.000000000 -0300
@@ -32,7 +32,7 @@
 #else
     struct statvfs* mounts = nullptr;
 #endif
+    int count = getmntinfo(&mounts, MNT_WAIT);
-    int count = getmntinfo(&mounts, 0);
     for (int32_t i = 0; i < count; i++)
     {
         onFound(mounts[i].f_mntonname);
