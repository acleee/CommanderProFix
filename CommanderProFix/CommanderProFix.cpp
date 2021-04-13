//
//  CommanderProFix.cpp
//  CommanderProFix
//
//  Copyright © 2021 aclee_. All rights reserved.
//  Thank you to vit9696 for making CommanderProFix and making this possible.

#include <IOKit/IOService.h>
#include <Headers/kern_api.hpp>
#include <Headers/plugin_start.hpp>
#include <Headers/kern_policy.hpp>

static const char *bootargOff[] {
	"-revoff"
};

static const char *bootargDebug[] {
	"-revdbg"
};

static const char *bootargBeta[] {
	"-revbeta"
};

static bool verboseProcessLogging;

struct CommanderProFixPolicy {

	/**
	 *  Policy to restrict blacklisted process execution
	 */
	static int policyCheckExecve(kauth_cred_t cred, struct vnode *vp, struct vnode *scriptvp, struct label *vnodelabel, struct label *scriptlabel, struct label *execlabel, struct componentname *cnp, u_int *csflags, void *macpolicyattr, size_t macpolicyattrlen) {

		static const char *procBlacklist[] {
            "/usr/libexec/ioupsd",
		};

		char pathbuf[MAXPATHLEN];
		int len = MAXPATHLEN;
		int err = vn_getpath(vp, pathbuf, &len);

		if (err == 0) {
			// Uncomment for more verbose output.
			DBGLOG_COND(verboseProcessLogging, "rev", "got request %s", pathbuf);

			for (auto &proc : procBlacklist) {
				if (strcmp(pathbuf, proc) == 0) {
					DBGLOG("rev", "restricting process %s", pathbuf);
					return EPERM;
				}
			}
		}

		return 0;
	}

	/**
	 *  Default dummy BSD init policy
	 */
	static void policyInitBSD(mac_policy_conf *conf) {
		DBGLOG("rev", "init bsd policy on %u", getKernelVersion());
	}

	/**
	 *  TrustedBSD policy options
	 */
	mac_policy_ops policyOps {
		.mpo_policy_initbsd = policyInitBSD,
		.mpo_vnode_check_exec = policyCheckExecve
	};

	/**
	 *  Full policy name
	 */
#ifdef DEBUG
	static constexpr const char *fullName {xStringify(PRODUCT_NAME) " Kernel Extension " xStringify(MODULE_VERSION) " DEBUG build"};
#else
	static constexpr const char *fullName {xStringify(PRODUCT_NAME) " Kernel Extension " xStringify(MODULE_VERSION)};
#endif

	/**
	 *  Policy controller
	 */
	Policy policy;

	/**
	 Policy constructor.
	 */
	CommanderProFixPolicy() : policy(xStringify(PRODUCT_NAME), fullName, &policyOps) {}
};

static CommanderProFixPolicy CommanderProFixPolicy;

PluginConfiguration ADDPR(config) {
	xStringify(PRODUCT_NAME),
	parseModuleVersion(xStringify(MODULE_VERSION)),
	LiluAPI::AllowNormal | LiluAPI::AllowInstallerRecovery | LiluAPI::AllowSafeMode,
	bootargOff,
	arrsize(bootargOff),
	bootargDebug,
	arrsize(bootargDebug),
	bootargBeta,
	arrsize(bootargBeta),
	KernelVersion::MountainLion,
	KernelVersion::BigSur,
	[]() {
		DBGLOG("rev", "restriction policy plugin loaded");
		verboseProcessLogging = checkKernelArgument("-revproc");
		CommanderProFixPolicy.policy.registerPolicy();
	}
};
