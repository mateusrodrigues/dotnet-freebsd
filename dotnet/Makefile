# $FreeBSD$

PORTNAME=	dotnet
DISTVERSIONPREFIX=	v
DISTVERSION=	6.1.0-preview.4
CATEGORIES=	devel

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

MAINTAINER=	mateus@mateus.tech
COMMENT=	.NET Core runtime

USE_GITHUB=	yes
GH_ACCOUNT=	dotnet
GH_PROJECT=	core-setup
GH_TUPLE=	dotnet:coreclr:5d34cc6:1/external/coreclr \
		dotnet:corefx:c7f7b5b:2/external/corefx

MAKE_JOBS_UNSAFE=	yes
BUILD_CONFIGURATION=	Release
MAKE_ENV=	COMPlus_ZapDisable=1 \
		COMPlus_ReadyToRun=0 \
		DOTNET_SKIP_FIRST_TIME_EXPERIENCE=1 \
		DOTNET_CLI_TELEMETRY_OPTOUT=1 \
		SSL_CERT_FILE=/usr/local/share/certs/ca-root-nss.crt \
		DOTNET_SYSTEM_NET_HTTP_USESOCKETSHTTPHANDLER=0

post-patch:

do-build:

.include <bsd.port.mk>
