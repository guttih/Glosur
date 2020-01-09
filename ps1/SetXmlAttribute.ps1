#Set Xml Attribute
#gudjonh@valitor.is
<#
    This script allows you to change xml attributes on a element.

param(
   
   [string]  $FullFileName, # Path and name of a xml file to change
   [string]  $XPath,        # XPath to the element containing the attribute to be changed
   [string]  $Attribute,    # Name of the Attribute to be changed
   [string]  $Value,        # The new value of the attribute
   
   [boolean] $SplittedValue,# Is the destination value splitted up into many strings, and we only want to change one of them Valid values are $true or $false
   [string]  $SplitIndex,   # If SplittedValue is $true then this is the index of the value string to be replaced
   [string]  $Delimiter,    # If SplittedValue is $true then this is the delimiter between the splitted strings.  default value is ";"
   [string]  $Action        # The action to be taken (for now, it is Always "SetAttribute"
)
#>
if (  [string]::IsNullOrEmpty($FullFileName))                       { throw "Parameter FullFileName is missing!"  }
if (  [string]::IsNullOrEmpty($XPath))                              { throw "Parameter XPath is missing!"         }
if (  [string]::IsNullOrEmpty($Attribute))                          { throw "Parameter Attribute is missing!"     }
if (  [string]::IsNullOrEmpty($Value))                              { $Value=""    }
if (  [string]::IsNullOrEmpty($Action))                             { throw "Parameter Action is missing!"        }
if (  [string]::IsNullOrEmpty($SplittedValue))                      { throw "Parameter SplittedValue is missing!" }
if (  ($SplittedValue -ne $true) -and ($SplittedValue -ne $false) ) { throw "Parameter SplittedValue is not true or false!" }

if($SplittedValue) { 
    if (  [string]::IsNullOrEmpty($SplitIndex)){ throw "Parameter SplitIndex is missing!"    }
    
        if (!($SplitIndex -match '^\d+$')) {
            throw "SplitIndex must be a number from 0 to n"
        }
        if ([string]::IsNullOrEmpty($Delimiter)   ) { 
            $Delimiter=";"  #the default 
        }     
}


function SplitAndReplaceIndexedText {
    Param ([string]$Text, [string]$Value, [int]$IndexToReplace, [string]$Delim)
    
    $Arr = $Text.Split($Delim);
    $Count = $Arr.Count;
    
    if ($Count -le 1) {
        throw "The value of this attribute is not split into sections"
    }
    if ($Count -le $IndexToReplace) {
        throw "SplitIndex $IndexToReplace is out of range,  there are only $Count sections"
    }

    $Arr[$IndexToReplace]=$Value;
    return [system.String]::Join(";", $Arr)
}

## XML Node names and Attributes are CaSe SeNsItIvE!
Write-Output "FullFileName : $FullFileName"

[XML]$xml = Get-Content $FullFileName
if (!$xml) { 
	throw "The file ""$FullFileName"" not found or not valid XML"; 
}

$XPathValue = $XPath + "/@"+$Attribute;

$elm = $xml.selectSingleNode($XPath)
if (!$elm) { throw "XPath ""$XPath"" not found in file" }

$ValueCurrent = $xml.selectSingleNode($XPathValue);
if (!$ValueCurrent) { throw "Value for current attribute not found.  XPath=""$ValueCurrent"""}

[string]$ValueOld = $xml.selectSingleNode($XPathValue).get_innerXml();

if ( $SplittedValue -eq $true)  {
    $Value = SplitAndReplaceIndexedText -Text $ValueOld -Value $Value -IndexToReplace $SplitIndex -Delim $Delimiter
}
Write-Output "Old value    : $ValueOld"

if ($Value -ne $ValueOld) {
    Write-Output "New value    : $Value"
    $elm.SetAttribute($Attribute, $Value);
    $xml.Save($FullFileName);
    
} else {
    Write-Output "New and old values are the same no need to save"
}

