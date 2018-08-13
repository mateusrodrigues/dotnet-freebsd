# $FreeBSD$

PORTNAME=	dotnet
DISTVERSION=	2.2.0-preview1-26620-03
CATEGORIES=	devel
MASTER_SITES=	https://gsocfiles.blob.core.windows.net/dotnet/
DISTFILES=	dotnet-freebsd-2.2.0-preview1-26620-03-MANAGEDONLY.tar.gz

MAINTAINER=	mateus@mateus.tech
COMMENT=	Dotnet is a cross-platform framework for building services and apps.

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE.TXT

BUILD_DEPENDS=	bash:shells/bash \
		cmake:devel/cmake \
		icuinfo:devel/icu
LIB_DEPENDS=	libcurl.so:ftp/curl \
		libgssapi_krb5.so:security/krb5 \
		libgssapi_krb5.so.2.2:security/krb5 \
		libunwind-x86_64.so:devel/libunwind \
		libunwind.so:devel/libunwind \
		liblttng-ust.so:sysutils/lttng-ust
USES=		gettext-runtime
USE_GITHUB=	yes
GH_ACCOUNT=	dotnet
GH_PROJECT=	core-setup
GH_TAGNAME=	2ad3de5
GH_TUPLE=	dotnet:coreclr:5d34cc6:1/external/coreclr \
		dotnet:corefx:c7f7b5b:2/external/corefx

MAKE_JOBS_UNSAFE=	yes
BUILD_CONFIGURATION=	release
RUNTIME_VERSION=	2.2.0-preview1-26620-03
CORE_SETUP_COMMIT_HASH=	2ad3de577c6552be4a06fa0c6b7313ad8b57fc41

do-build:
	(cd ${WRKSRC} && \
		src/corehost/build.sh --configuration ${BUILD_CONFIGURATION} --hostver "2.0.0" \
			--arch "x`echo ${ARCH} | ${SED} 's/[^0-9]*//g'`" --apphostver "2.0.0" \
		       	--fxrver "2.0.0" --policyver "2.0.0" --commithash ${CORE_SETUP_COMMIT_HASH})
	(cd ${WRKSRC}/external/coreclr && \
		./build.sh -clang3.8 -skipmscorlib -${BUILD_CONFIGURATION})
	(cd ${WRKSRC}/external/corefx && \
		src/Native/build-native.sh -${BUILD_CONFIGURATION})

do-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/share/dotnet/shared
	(cd ${WRKDIR}/shared && \
		${COPYTREE_SHARE} . ${STAGEDIR}${PREFIX}/share/dotnet/shared)

	(cd ${WRKSRC}/cli/dll && \
		${INSTALL_LIB} libhostpolicy.so ${STAGEDIR}${PREFIX}/share/dotnet/shared/Microsoft.NETCore.App/${RUNTIME_VERSION})
	(cd ${WRKSRC}/cli/exe/dotnet && \
		${INSTALL_PROGRAM} dotnet ${STAGEDIR}${PREFIX}/share/dotnet)
	${MKDIR} ${STAGEDIR}${PREFIX}/share/dotnet/host/fxr/${RUNTIME_VERSION}
	(cd ${WRKSRC}/cli/fxr && \
     		${INSTALL_LIB} libhostfxr.so ${STAGEDIR}${PREFIX}/share/dotnet/host/fxr/${RUNTIME_VERSION})

	${INSTALL_LIB} ${WRKSRC}/external/coreclr/bin/Product/FreeBSD.x64.Release/*.so ${STAGEDIR}${PREFIX}/share/dotnet/shared/Microsoft.NETCore.App/${RUNTIME_VERSION}
	${INSTALL_DATA} ${WRKSRC}/external/coreclr/bin/Product/FreeBSD.x64.Release/System.Globalization.Native.a ${STAGEDIR}${PREFIX}/share/dotnet/shared/Microsoft.NETCore.App/${RUNTIME_VERSION}
	${INSTALL_PROGRAM} ${WRKSRC}/external/coreclr/bin/Product/FreeBSD.x64.Release/corerun ${STAGEDIR}${PREFIX}/share/dotnet/shared/Microsoft.NETCore.App/${RUNTIME_VERSION}
	${INSTALL_PROGRAM} ${WRKSRC}/external/coreclr/bin/Product/FreeBSD.x64.Release/crossgen ${STAGEDIR}${PREFIX}/share/dotnet/shared/Microsoft.NETCore.App/${RUNTIME_VERSION}
	${CP} ${STAGEDIR}${PREFIX}/share/dotnet/dotnet ${STAGEDIR}${PREFIX}/share/dotnet/shared/Microsoft.NETCore.App/${RUNTIME_VERSION}/corehost

	${INSTALL_LIB} ${WRKSRC}/external/corefx/bin/FreeBSD.x64.Release/native/*.so ${STAGEDIR}${PREFIX}/share/dotnet/shared/Microsoft.NETCore.App/${RUNTIME_VERSION}
	${INSTALL_DATA} ${WRKSRC}/external/corefx/bin/FreeBSD.x64.Release/native/*.a ${STAGEDIR}${PREFIX}/share/dotnet/shared/Microsoft.NETCore.App/${RUNTIME_VERSION}

	${INSTALL_MAN} ${WRKDIR}/LICENSE.txt ${STAGEDIR}${PREFIX}/share/dotnet
	${INSTALL_MAN} ${WRKDIR}/ThirdPartyNotices.txt ${STAGEDIR}${PREFIX}/share/dotnet
	${INSTALL_MAN} ${WRKSRC}/external/coreclr/bin/Product/FreeBSD.x64.Release/sosdocsunix.txt ${STAGEDIR}${PREFIX}/share/dotnet/shared/Microsoft.NETCore.App/${RUNTIME_VERSION}

.include <bsd.port.mk>
