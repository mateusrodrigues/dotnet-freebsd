# Created by: Mateus de Morais <mateus@mateus.tech>
# $FreeBSD$

PORTNAME=	dotnet-sdk
DISTVERSION=	3.0.100-preview1-009019
CATEGORIES=	devel
MASTER_SITES=	https://gsocfiles.blob.core.windows.net/dotnet/:sdk
DISTFILES=	dotnet-sdk-freebsd-3.0.100-preview1-009019.tar.gz:sdk

MAINTAINER=	mateus@mateus.tech
COMMENT=	Open Source SDK to build .NET Core applications

LICENSE=	MIT

ONLY_FOR_ARCHS=	amd64 i386

RUN_DEPENDS=	dotnet:devel/dotnet

USE_GITHUB=	yes
GH_TUPLE=	dotnet:core-setup:2ad3de5:DEFAULT

MAKE_JOBS_UNSAFE=	yes
SDK_VERSION=	3.0.100-preview1-009019
BUILD_CONFIGURATION=	release
CORE_SETUP_VERSION=	2.0.0
CORE_SETUP_COMMIT_HASH=	2ad3de577c6552be4a06fa0c6b7313ad8b57fc41

.include <bsd.port.pre.mk>

.if ${ARCH} == i386
CORE_SETUP_ARCH=        x86
.elif ${ARCH} == amd64
CORE_SETUP_ARCH=        x64
.endif

do-build:
	(cd ${WRKSRC} && \
		src/corehost/build.sh \
			--configuration ${BUILD_CONFIGURATION} \
			--hostver "${CORE_SETUP_VERSION}" \
			--arch "${CORE_SETUP_ARCH}" \
		       	--apphostver "${CORE_SETUP_VERSION}" \
			--fxrver "${CORE_SETUP_VERSION}" \
			--policyver "${CORE_SETUP_VERSION}" \
			--commithash ${CORE_SETUP_COMMIT_HASH})

do-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/share/dotnet/sdk/${SDK_VERSION}
	(cd ${WRKDIR} && \
		${COPYTREE_SHARE} ${SDK_VERSION} ${STAGEDIR}${PREFIX}/share/dotnet/sdk)
	${RM} ${STAGEDIR}${PREFIX}/share/dotnet/sdk/${SDK_VERSION}/*.so
	(cd ${WRKSRC}/cli/dll && \
		${INSTALL_LIB} libhostpolicy.so ${STAGEDIR}${PREFIX}/share/dotnet/sdk/${SDK_VERSION})
	(cd ${WRKSRC}/cli/fxr && \
		${INSTALL_LIB} libhostfxr.so ${STAGEDIR}${PREFIX}/share/dotnet/sdk/${SDK_VERSION})

.include <bsd.port.mk>
