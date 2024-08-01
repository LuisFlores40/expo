import type { ExpoConfig } from '@expo/config-types';
import fs from 'node:fs';
import xcode, { type XCBuildConfiguration } from 'xcode';

import { getAllPBXProjectPaths } from './Paths';
import { getNativeTargets } from './Target';
import { getBuildConfigurationsForListId } from './utils/Xcodeproj';
import { trimQuotes } from './utils/string';
import type { ConfigPlugin, XcodeProject } from '../Plugin.types';
import { withXcodeProject } from '../plugins/ios-plugins';

/**
 * Set the Apple development team ID for all build configurations using the first native target.
 */
export const withDevelopmentTeam: ConfigPlugin<{ developmentTeam?: string } | void> = (
  config,
  { developmentTeam } = {}
) => {
  return withXcodeProject(config, (config) => {
    // TODO: maybe infer from `EXPO_APPLE_TEAM_ID` env variable?
    const teamId = developmentTeam ?? getDevelopmentTeam(config);
    if (teamId) {
      config.modResults = updateDevelopmentTeamForPbxproj(config.modResults, teamId);
    }

    return config;
  });
};

/** Get the Apple development team ID from Expo config, if defined */
export function getDevelopmentTeam(config: Pick<ExpoConfig, 'ios'>): string | null {
  return config.ios?.developmentTeam ?? null;
}

/** Set the Apple development team ID for an XCBuildConfiguration object */
export function setDevelopmentTeamForBuildConfiguration(
  xcBuildConfiguration: XCBuildConfiguration,
  developmentTeam?: string
): void {
  if (developmentTeam) {
    xcBuildConfiguration.buildSettings.DEVELOPMENT_TEAM = trimQuotes(developmentTeam);
  } else {
    delete xcBuildConfiguration.buildSettings.DEVELOPMENT_TEAM;
  }
}

/**
 * Update the Apple development team ID for all XCBuildConfiguration entries, in all native targets.
 *
 * A development team is stored as a value in XCBuildConfiguration entry.
 * Those entries exist for every pair (build target, build configuration).
 * Unless target name is passed, the first target defined in the pbxproj is used
 * (to keep compatibility with the inaccurate legacy implementation of this function).
 */
export function updateDevelopmentTeamForPbxproj(
  project: XcodeProject,
  developmentTeam?: string
): XcodeProject {
  const nativeTargets = getNativeTargets(project);

  nativeTargets.forEach(([, nativeTarget]) => {
    getBuildConfigurationsForListId(project, nativeTarget.buildConfigurationList).forEach(
      ([, buildConfig]) => setDevelopmentTeamForBuildConfiguration(buildConfig, developmentTeam)
    );
  });

  return project;
}

/**
 * Updates the Apple development team ID for pbx projects inside the ios directory of the given project root
 *
 * @param {string} projectRoot Path to project root containing the ios directory
 * @param {[string]} developmentTeam Desired Apple development team ID
 */
export function setDevelopmentTeamForPbxproj(projectRoot: string, developmentTeam?: string): void {
  // Get all pbx projects in the ${projectRoot}/ios directory
  const pbxprojPaths = getAllPBXProjectPaths(projectRoot);

  for (const pbxprojPath of pbxprojPaths) {
    let project = xcode.project(pbxprojPath);
    project.parseSync();
    project = updateDevelopmentTeamForPbxproj(project, developmentTeam);
    fs.writeFileSync(pbxprojPath, project.writeSync());
  }
}
