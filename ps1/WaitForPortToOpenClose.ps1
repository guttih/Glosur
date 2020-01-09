#Wait for port(s) to open/close
#gudjonh@valitor.is
 #waits for specific ports to close.
 
 $Result =""

if (([string]::IsNullOrEmpty($Port1) -And [string]::IsNullOrEmpty($Port2)) -Or [string]::IsNullOrEmpty($Port1)) {
    Write-Output "Port missing"
    exit 1
}

 function WaitForPortsToClose {
  $RetryAttempt = $RetryAttempt + 1
  
  if ([string]::IsNullOrEmpty($Port2)) {
    $Result = Get-NetTCPConnection -LocalPort $Port1 -ErrorAction SilentlyContinue
  } else {
    $Result = Get-NetTCPConnection -LocalPort $Port1,$Port2 -ErrorAction SilentlyContinue
  }
  
 
    if ([string]::IsNullOrEmpty($Result)){
        Write-Output "No ports open"
        exit 0
     } Else {
        Write-Output "Open port(s), check $RetryAttempt"
        if ($RetryAttempt -ge $RetryMax) {
             throw "Maximum retries reached"
        }

        Start-Sleep $RetryAfter
        WaitForPortsToClose
     }
 }

  function WaitForPortsToOpen {
  
      $RetryAttempt = $RetryAttempt + 1
  
      if ([string]::IsNullOrEmpty($Port2)) {
        $Result = Get-NetTCPConnection -LocalPort $Port1 -ErrorAction SilentlyContinue
      } else {
        $Result = Get-NetTCPConnection -LocalPort $Port1,$Port2 -ErrorAction SilentlyContinue
      }
 
      if (-Not ([string]::IsNullOrEmpty($Result))){
          Write-Output "Port(s) are open"
          exit 0
          } Else {
              Write-Output "No ports open, check $RetryAttempt"
              if ($RetryAttempt -ge $RetryMax) {
                   throw "Maximum retries reached"
              }
              Start-Sleep $RetryAfter
              WaitForPortsToOpen
          }
 }


 if ($WaitForAction -eq "Open") {
    WaitForPortsToOpen
 } else {
    WaitForPortsToClose
 }
