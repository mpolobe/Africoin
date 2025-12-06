# Auto-Review and Auto-Merge Setup

This repository has automated workflows to review and merge pull requests.

## How It Works

### Automatic Review & Merge
Pull requests from trusted sources (Copilot bot, repository owner) are automatically:
1. ✅ Reviewed for basic validation
2. ✅ Checked for security issues
3. ✅ Approved if all checks pass
4. ✅ Merged automatically

### Trusted Sources
- `copilot-swe-agent`
- `Copilot`
- Repository owner

### Manual Override
You can manually trigger auto-merge for any PR:
1. Go to Actions tab
2. Select "Auto Review and Merge" workflow
3. Click "Run workflow"
4. Enter PR number
5. Run

## Security Checks
- ✅ No .git directory modifications
- ✅ No hardcoded credentials
- ✅ Valid shell script syntax
- ✅ Markdown validation

## Branch Cleanup
Merged branches are automatically deleted to keep the repository clean.

## Disabling Auto-Merge
To disable for specific PRs, add label: `no-auto-merge`
