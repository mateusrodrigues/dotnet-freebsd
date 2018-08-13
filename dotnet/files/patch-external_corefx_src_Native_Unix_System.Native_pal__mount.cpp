--- external/corefx/src/Native/Unix/System.Native/pal_mount.cpp.orig	2018-06-19 23:42:29 UTC
+++ external/corefx/src/Native/Unix/System.Native/pal_mount.cpp
@@ -32,7 +32,7 @@ static int32_t GetMountInfo(MountPointFo
 #else
     struct statvfs* mounts = nullptr;
 #endif
-    int count = getmntinfo(&mounts, 0);
+    int count = getmntinfo(&mounts, MNT_WAIT);
     for (int32_t i = 0; i < count; i++)
     {
         onFound(mounts[i].f_mntonname);
