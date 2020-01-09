#Check StatusPage Version
#gudjonh@valitor.is
Write-Output "StatusPage URL           : $StatusPageURL"
Write-Output "Release version          : $VersionToCheck"
Write-Output "Compare whole version    : $CompareWholeVersion"

if (-not ([string]::IsNullOrEmpty($SecurityProtocol)))
{
	Write-Output "SecurityProtocol         : $SecurityProtocol"
    [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::$SecurityProtocol
}

# Adds zero to start of all numbers less than 10
function FixVersionNumbers {
    Param ([string]$version);
    $Arr = $version.Split(".");
    $Count = $Arr.Count;
    if ($Count -le 3) {
        throw "Invalid version number ""$version""";
    }
    
    for ($i=0; $i -lt $Count; $i++) {
        if($Arr[$i] -match "^\d+$")
        {
            $Arr[$i] = $Arr[$i].PadLeft(2,'0');
        }
    }
   
    return [system.String]::Join(".", $Arr);
}

$Data                 = Invoke-WebRequest -Uri $StatusPageURL
$PageVersion          = $Data.ParsedHtml.getElementById("$serverVersionId").innerHTML

$VersionToCheck = FixVersionNumbers -version $VersionToCheck;
$PageVersion    = FixVersionNumbers -version $PageVersion;
$VersionToCheckModified = $VersionToCheck;
$PageVersionModified  = $PageVersion;

If ($CompareWholeVersion -ne "true") {
    #We are not going to compare the last digit
     $DotCount = ($VersionToCheck.ToCharArray() | Where-Object {$_ -eq '.'} | Measure-Object).Count
    If ($DotCount -ge 3) {
        $VersionToCheckModified = $VersionToCheck.Substring(0,$VersionToCheck.LastIndexOf('.'));
    } else {
        $CheckVersionModified = $VersionToCheck;
    }
    
    $PageVersionModified  = $PageVersion.Substring(0, $PageVersion.LastIndexOf('.'));
}

Write-Output "StatusPage version       : $PageVersion"
Write-Output "Release compare string   : $VersionToCheckModified"
Write-Output "Statuspage compare string: $PageVersionModified"

If ($PageVersionModified -ne $VersionToCheckModified) {
    throw 'Server versions do not match'
}
