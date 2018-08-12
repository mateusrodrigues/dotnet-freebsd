# $FreeBSD$

PORTNAME=	dotnet
DISTVERSIONPREFIX=	v
DISTVERSION=	3.0.100-preview1-009019
CATEGORIES=	devel

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE.TXT

MAINTAINER=	mateus@mateus.tech
COMMENT=	.NET Core runtime

MASTER_SITES=	https://gsocfiles.blob.core.windows.net/dotnet/
DISTFILES=	dotnet-freebsd-3.0.100-preview1-009019-MANAGEDONLY.tar.gz
USE_GITHUB=	yes
GH_ACCOUNT=	dotnet
GH_PROJECT=	core-setup
GH_TAGNAME=	2ad3de5
GH_TUPLE=	dotnet:coreclr:5d34cc6:1/external/coreclr \
		dotnet:corefx:c7f7b5b:2/external/corefx

USES=		gettext-runtime
BUILD_DEPENDS=	bash:shells/bash \
		cmake:devel/cmake \
		icuinfo:devel/icu \
		libcurl.so:ftp/curl \
		libgssapi_krb5.so:secutiry/krb5 \
		libunwind-x86_64.so:devel/libunwind \
		linunwind.sp:devel/libunwind \
		liblttng-ust.so:sysutils/lttng-ust
LIB_DEPENDS=	libcurl.so:ftp/curl \
		libgssapi_krb5.so:security/krb5 \
		libunwind-x86_64.so:devel/libunwind \
		libunwind.so:devel/libunwind \
		liblttng-ust.so:sysutils/lttng-ust

MAKE_JOBS_UNSAFE=	yes
BUILD_CONFIGURATION=	release
RUNTIME_VERSION=	2.2.0-preview1-26620-03
CORE_SETUP_COMMIT_HASH=	2ad3de577c6552be4a06fa0c6b7313ad8b57fc41
MAKE_ENV=	COMPlus_ZapDisable=1 \
		COMPlus_ReadyToRun=0 \
		DOTNET_SKIP_FIRST_TIME_EXPERIENCE=1 \
		DOTNET_CLI_TELEMETRY_OPTOUT=1 \
		SSL_CERT_FILE=/usr/local/share/certs/ca-root-nss.crt \
		DOTNET_SYSTEM_NET_HTTP_USESOCKETSHTTPHANDLER=0

do-build:
	(cd ${WRKSRC} && \
		src/corehost/build.sh --configuration ${BUILD_CONFIGURATION} --hostver "2.0.0" \
			--arch "x`echo ${ARCH} | sed 's/[^0-9]*//g'`" --apphostver "2.0.0" \
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
	#${INSTALL_PROGRAM} ${WRKSRC}/external/coreclr/bin/Product/FreeBSD.x64.Release/corehost ${STAGEDIR}${PREFIX}/share/dotnet/shared/Microsoft.NETCore.App/${RUNTIME_VERSION}
	${INSTALL_PROGRAM} ${WRKSRC}/external/coreclr/bin/Product/FreeBSD.x64.Release/corerun ${STAGEDIR}${PREFIX}/share/dotnet/shared/Microsoft.NETCore.App/${RUNTIME_VERSION}
	#${INSTALL_PROGRAM} ${WRKSRC}/external/coreclr/bin/Product/FreeBSD.x64.Release/createdump ${STAGEDIR}${PREFIX}/share/dotnet/shared/Microsoft.NETCore.App/${RUNTIME_VERSION}
	${INSTALL_PROGRAM} ${WRKSRC}/external/coreclr/bin/Product/FreeBSD.x64.Release/crossgen ${STAGEDIR}${PREFIX}/share/dotnet/shared/Microsoft.NETCore.App/${RUNTIME_VERSION}

	${INSTALL_LIB} ${WRKSRC}/external/corefx/bin/FreeBSD.x64.Release/native/*.so ${STAGEDIR}${PREFIX}/share/dotnet/shared/Microsoft.NETCore.App/${RUNTIME_VERSION}
	${INSTALL_DATA} ${WRKSRC}/external/corefx/bin/FreeBSD.x64.Release/native/*.a ${STAGEDIR}${PREFIX}/share/dotnet/shared/Microsoft.NETCore.App/${RUNTIME_VERSION}

	${INSTALL_MAN} ${WRKDIR}/LICENSE.txt ${STAGEDIR}${PREFIX}/share/dotnet
	${INSTALL_MAN} ${WRKDIR}/ThirdPartyNotices.txt ${STAGEDIR}${PREFIX}/share/dotnet

.include <bsd.port.mk>
