# $FreeBSD$

PORTNAME=	dotnet
DISTVERSIONPREFIX=	v
DISTVERSION=	3.0.100-preview1-009019
CATEGORIES=	devel

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE.TXT

MAINTAINER=	mateus@mateus.tech
COMMENT=	.NET Core runtime

USE_GITHUB=	yes
GH_ACCOUNT=	dotnet
GH_PROJECT=	core-setup
GH_TAGNAME=	2ad3de5
GH_TUPLE=	dotnet:coreclr:5d34cc6:1/external/coreclr \
		dotnet:corefx:c7f7b5b:2/external/corefx

MAKE_JOBS_UNSAFE=	yes
BUILD_CONFIGURATION=	release
CORE_SETUP_COMMIT_HASH=	2ad3de577c6552be4a06fa0c6b7313ad8b57fc41
MAKE_ENV=	COMPlus_ZapDisable=1 \
		COMPlus_ReadyToRun=0 \
		DOTNET_SKIP_FIRST_TIME_EXPERIENCE=1 \
		DOTNET_CLI_TELEMETRY_OPTOUT=1 \
		SSL_CERT_FILE=/usr/local/share/certs/ca-root-nss.crt \
		DOTNET_SYSTEM_NET_HTTP_USESOCKETSHTTPHANDLER=0

do-configure:
	(cd ${WRKSRC}/external/coreclr && \
		${WRKSRC}/external/coreclr/build.sh -configureonly -skipmscorlib -${BUILD_CONFIGURATION})

do-build:
	(cd ${WRKSRC} && \
		src/corehost/build.sh --configuration ${BUILD_CONFIGURATION} --hostver "2.0.0" \
			--arch "x`echo ${ARCH} | sed 's/[^0-9]*//g'`" --apphostver "2.0.0" \
		       	--fxrver "2.0.0" --policyver "2.0.0" --commithash ${CORE_SETUP_COMMIT_HASH})
	(cd ${WRKSRC}/external/coreclr && \
		build.sh -skipconfigure -skipmscorlib -${BUILD_CONFIGURATION})
	(cd ${WRKSRC}/external/corefx && \
		src/Native/build-native.sh -${BUILD_CONFIGURATION})

.include <bsd.port.mk>
