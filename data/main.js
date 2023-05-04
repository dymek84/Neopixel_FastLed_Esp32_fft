function paletteTimeSelect () {
  var time = document.getElementById('paletteTime').value
  var data = { paletteTime: time }
  var xhr = new XMLHttpRequest()
  var url = '/paletteTime'
  xhr.addEventListener('load', transferComplete)
  xhr.addEventListener('error', transferFailed)
  xhr.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var response = JSON.parse(xhr.responseText)
      let element = document.getElementById('paletteTime')
      element.value = response.paletteTime
      if (xhr.responseText != null) {
        console.log(xhr.responseText)
      }
    }
  }
  xhr.open('POST', url, true)
  xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  xhr.send(JSON.stringify(data))
  return true
}
function clockColor (hexColor) {
  var data = { clockColor: hexColor }
  var xhr = new XMLHttpRequest()
  var url = '/clockColor'
  xhr.addEventListener('load', transferComplete)
  xhr.addEventListener('error', transferFailed)
  xhr.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var response = JSON.parse(xhr.responseText)

      if (xhr.responseText != null) {
        console.log(xhr.responseText)
      }
    }
  }
  xhr.open('POST', url, true)
  xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  xhr.send(JSON.stringify(data))
  return true
}
function onOffClock (event) {
 
  data = { onOffClock: event }
  var xhr = new XMLHttpRequest()
  var url = '/onoffClock'
  xhr.addEventListener('load', transferComplete)
  xhr.addEventListener('error', transferFailed)
  xhr.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var response = JSON.parse(xhr.responseText)
      document.getElementById('onOffClock').innerHTML =
        'The clock is ' + response.onOffClock
      if (xhr.responseText != null) {
        console.log(xhr.responseText)
      }
    }
  }
  xhr.open('POST', url, true)
  xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  xhr.send(JSON.stringify(data))
  return true
}
function PatternMatrix (name) {
  var data = { patterns: name }
  var xhr = new XMLHttpRequest()
  var url = '/patterns'
  xhr.addEventListener('load', transferComplete)
  xhr.addEventListener('error', transferFailed)
  xhr.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var response = JSON.parse(xhr.responseText)
      document.getElementById('patMatName').innerHTML =
        response.patternMatrixName
      document.getElementById('isAudio').innerHTML = response.isAudio

      var max = response.maxPatMat
      var current = response.curPatMat
      document.getElementById('patMatNumber').innerHTML = current + '/' + max
      if (xhr.responseText != null) {
        console.log(xhr.responseText)
      }
    }
  }
  xhr.open('POST', url, true)
  xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  xhr.send(JSON.stringify(data))
  return true
}

function autopalletteMatrix (event) {
  var data
  if (document.querySelector('#checkBoxMatrix').checked) {
    console.log('checked')
    data = '1'
  } else {
    console.log('unchecked')
    data = '0'
  }
  data = { autoPalMatrix: data }
  var xhr = new XMLHttpRequest()
  var url = '/checkBoxM'
  xhr.addEventListener('load', transferComplete)
  xhr.addEventListener('error', transferFailed)
  xhr.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var response = JSON.parse(xhr.responseText)

      if (xhr.responseText != null) {
        console.log(xhr.responseText)
      }
    }
  }
  xhr.open('POST', url, true)
  xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  xhr.send(JSON.stringify(data))
  return true
}
function autopalletteStripe (event) {
  var is
  if (document.querySelector('#squaredThree').checked) {
    console.log('checked')
    is = 1
  } else {
    console.log('unchecked')
    is = 0
  }
  data = { autoPalStripe: is }
  var xhr = new XMLHttpRequest()
  var url = '/checkBoxS'
  xhr.addEventListener('load', transferComplete)
  xhr.addEventListener('error', transferFailed)
  xhr.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var response = JSON.parse(xhr.responseText)

      if (xhr.responseText != null) {
        console.log(xhr.responseText)
      }
    }
  }
  xhr.open('POST', url, true)
  xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  xhr.send(JSON.stringify(data))
  return true
}
function PatternStripe (name) {
  var data = { patterns: name }
  var xhr = new XMLHttpRequest()
  var url = '/patterns'
  xhr.addEventListener('load', transferComplete)
  xhr.addEventListener('error', transferFailed)
  xhr.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var response = JSON.parse(xhr.responseText)
      document.getElementById('patStrName').innerHTML =
        response.patternStripeName

      document.getElementById('isAudio').innerHTML = response.isAudio
      var max = response.maxPatStr
      var current = response.curPatStr
      document.getElementById('patStrNumber').innerHTML = current + '/' + max

      if (xhr.responseText != null) {
        console.log(xhr.responseText)
      }
    }
  }
  xhr.open('POST', url, true)
  xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  xhr.send(JSON.stringify(data))
  return true
}
function PaletteStripe (name) {
  var data = { palette: name }
  var xhr = new XMLHttpRequest()
  var url = '/palette'
  xhr.addEventListener('load', transferComplete)
  xhr.addEventListener('error', transferFailed)
  xhr.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var response = JSON.parse(xhr.responseText)
      document.getElementById('palStrName').innerHTML =
        response.paletteStripeName
      if (xhr.responseText != null) {
        console.log(xhr.responseText)
      }
    }
  }
  xhr.open('POST', url, true)
  xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  xhr.send(JSON.stringify(data))
  return true
}
function PaletteMatrix (name) {
  var data = { palette: name }
  var xhr = new XMLHttpRequest()
  var url = '/palette'
  xhr.addEventListener('load', transferComplete)
  xhr.addEventListener('error', transferFailed)
  xhr.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var response = JSON.parse(xhr.responseText)
      document.getElementById('palMatName').innerHTML =
        response.paletteMatrixName
      if (xhr.responseText != null) {
        console.log(xhr.responseText)
      }
    }
  }
  xhr.open('POST', url, true)
  xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  xhr.send(JSON.stringify(data))
  return true
}
function showMessage () {
  var xmessage = document.getElementById('WMessage').value

  var data = { message: xmessage }
  var xhr = new XMLHttpRequest()
  var url = '/showMessage'
  xhr.addEventListener('load', transferComplete)
  xhr.addEventListener('error', transferFailed)
  xhr.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var response = JSON.parse(xhr.responseText)

      if (xhr.responseText != null) {
        console.log(xhr.responseText)
      }
    }
  }
  xhr.open('POST', url, true)
  xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  xhr.send(JSON.stringify(data))
  return true
}
function setMessage () {
  console.log('save button was clicked!')
  var xmessage = document.getElementById('WMessage').value
  document.getElementById('messageHolder').innerHTML = '(' + xmessage + ')'
  var data = { message: xmessage }
  var xhr = new XMLHttpRequest()
  var url = '/message'
  xhr.addEventListener('load', transferComplete)
  xhr.addEventListener('error', transferFailed)
  xhr.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var response = JSON.parse(xhr.responseText)
      document.getElementById('messageHolder').innerHTML = response.message
      if (xhr.responseText != null) {
        console.log(xhr.responseText)
      }
    }
  }
  xhr.open('POST', url, true)
  xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  xhr.send(JSON.stringify(data))
  return true
}

function transferComplete (evt) {
  SnackBar({
    message: 'Data successfully sent',
    timeout: 1000,
    status: 'success'
  })
}

function transferFailed (evt) {
  SnackBar({
    message: 'Oops, something went wrong..',
    timeout: 1000,
    status: 'danger'
  })
}

function rangeMatrixBright (value) {
  document.getElementById('rangeValueMBright').innerHTML = value
  var xbrightness = value
  var data = { Mbrightness: xbrightness }
  var xhr = new XMLHttpRequest()
  var url = '/mBright'
  xhr.addEventListener('load', transferComplete)
  xhr.addEventListener('error', transferFailed)
  xhr.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      if (xhr.responseText != null) {
        console.log(xhr.responseText)
      }
    }
  }
  xhr.open('POST', url, true)
  xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  xhr.send(JSON.stringify(data))
  return true
}
function rangeStripBright (value) {
  document.getElementById('rangeValueSBright').innerHTML = value
  var xbrightness = value
  var data = { Sbrightness: xbrightness }
  var xhr = new XMLHttpRequest()
  var url = '/sBright'
  xhr.addEventListener('load', transferComplete)
  xhr.addEventListener('error', transferFailed)

  xhr.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      if (xhr.responseText != null) {
        console.log(xhr.responseText)
      }
    }
  }
  xhr.open('POST', url, true)
  xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  xhr.send(JSON.stringify(data))
  return true
}
function rangeStripSpeed (value) {
  document.getElementById('rangeValueSSpeed').innerHTML = value
  var speed = value
  var data = { stripeSpeed: speed }

  var xhr = new XMLHttpRequest()
  var url = '/sSpeed'

  xhr.addEventListener('load', transferComplete)
  xhr.addEventListener('error', transferFailed)

  xhr.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      if (xhr.responseText != null) {
        console.log(xhr.responseText)
      }
    }
  }
  xhr.open('POST', url, true)
  xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  xhr.send(JSON.stringify(data))
  return true
}
function rangeMatrixSpeed (value) {
  document.getElementById('rangeValueMSpeed').innerHTML = value
  var speed = value
  var data = { matrixSpeed: speed }

  var xhr = new XMLHttpRequest()
  var url = '/mSpeed'

  xhr.addEventListener('load', transferComplete)
  xhr.addEventListener('error', transferFailed)

  xhr.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      if (xhr.responseText != null) {
        console.log(xhr.responseText)
      }
    }
  }
  xhr.open('POST', url, true)
  xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  xhr.send(JSON.stringify(data))
  return true
}
function rangeNoise (value) {
  document.getElementById('rangeValueNoise').innerHTML = value
  var noise = value
  var data = { micNoise: noise }
  var xhr = new XMLHttpRequest()
  var url = '/micNoise'
  xhr.addEventListener('load', transferComplete)
  xhr.addEventListener('error', transferFailed)

  xhr.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      if (xhr.responseText != null) {
        console.log(xhr.responseText)
      }
    }
  }
  xhr.open('POST', url, true)
  xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  xhr.send(JSON.stringify(data))
  return true
}
function rangeMicSens (value) {
  document.getElementById('rangeValueMicSens').innerHTML = value
  var sens = value
  var data = { micSens: sens }

  var xhr = new XMLHttpRequest()
  var url = '/micSens'

  xhr.addEventListener('load', transferComplete)
  xhr.addEventListener('error', transferFailed)

  xhr.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      if (xhr.responseText != null) {
        console.log(xhr.responseText)
      }
    }
  }
  xhr.open('POST', url, true)
  xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  xhr.send(JSON.stringify(data))
  return true
}
function SnackBar (userOptions) {
  var _This = this

  var _Interval

  var _Element

  var _Container

  var _Message

  var _MessageWrapper

  function _create () {
    _applyUserOptions()

    _setContainer()

    _applyPositionClasses()

    _Element = _createMessage()

    _Container.appendChild(_Element)

    if (_Options.timeout !== false && _Options.timeout > 0) {
      _Interval = setTimeout(_This.Close, _Options.timeout)
    }
  }

  function _applyUserOptions () {
    _Options = {
      message: userOptions?.message ?? 'Operation performed successfully.',
      dismissible: userOptions?.dismissible ?? true,
      timeout: userOptions?.timeout ?? 5000,
      status: userOptions?.status
        ? userOptions.status.toLowerCase().trim()
        : '',
      actions: userOptions?.actions ?? [],
      fixed: userOptions?.fixed ?? false,
      position: userOptions?.position ?? 'bc',
      container: userOptions?.container ?? document.body,
      width: userOptions?.width,
      speed: userOptions?.speed,
      icon: userOptions?.icon
    }
  }

  function _setContainer () {
    var target = getOrFindContainer()

    if (target === undefined) {
      console.warn(
        'SnackBar: Could not find target container ' + _Options.container
      )
      target = document.body // default to the body as the container
    }

    _Container = getOrAddContainerIn(target)

    function getOrAddContainerIn (target) {
      var node

      var positionClass = _getPositionClass()

      for (var i = 0; i < target.children.length; i++) {
        node = target.children.item(i)

        if (
          node.nodeType === 1 &&
          node.classList.length > 0 &&
          node.classList.contains('js-snackbar-container') &&
          node.classList.contains(positionClass)
        ) {
          return node
        }
      }

      return createNewContainer(target)
    }

    function createNewContainer (target) {
      var container = document.createElement('div')
      container.classList.add('js-snackbar-container')

      if (_Options.fixed) {
        container.classList.add('js-snackbar-container--fixed')
      }

      target.appendChild(container)
      return container
    }

    function getOrFindContainer () {
      return typeof _Options.container === 'string'
        ? document.querySelector(_Options.container)
        : _Options.container
    }
  }

  function _applyPositionClasses () {
    _Container.classList.add(_getPositionClass())

    var fixedClassName = 'js-snackbar-container--fixed'

    if (_Options.fixed) {
      _Container.classList.add(fixedClassName)
    } else {
      _Container.classList.remove(fixedClassName)
    }
  }

  function _createMessage () {
    var outerElement = createWrapper()
    var innerSnack = createInnerSnackbar()
    outerElement.appendChild(innerSnack)
    return outerElement

    function createWrapper () {
      var outerElement = document.createElement('div')
      outerElement.classList.add('js-snackbar__wrapper')
      outerElement.style.height = '0px'
      outerElement.style.opacity = '0'
      outerElement.style.marginTop = '0px'
      outerElement.style.marginBottom = '0px'
      setWidth(outerElement)
      setSpeed(outerElement)
      return outerElement
    }

    function createInnerSnackbar () {
      var innerSnack = document.createElement('div')
      innerSnack.classList.add('js-snackbar', 'js-snackbar--show')
      applyColorAndIconTo(innerSnack)
      insertMessageTo(innerSnack)
      addActionsTo(innerSnack)
      addDismissButtonTo(innerSnack)
      return innerSnack
    }

    function applyColorAndIconTo (element) {
      if (!_Options.status) return
      var status = document.createElement('span')
      status.classList.add('js-snackbar__status')
      applyColorTo(status)
      applyIconTo(status)
      element.appendChild(status)

      function applyColorTo (element) {
        switch (_Options.status) {
          case 'success':
          case 'green':
            element.classList.add('js-snackbar--success')
            break

          case 'warning':
          case 'alert':
          case 'orange':
            element.classList.add('js-snackbar--warning')
            break

          case 'danger':
          case 'error':
          case 'red':
            element.classList.add('js-snackbar--danger')
            break

          default:
            element.classList.add('js-snackbar--info')
            break
        }
      }

      function applyIconTo (element) {
        if (!_Options.icon) return
        var icon = document.createElement('span')
        icon.classList.add('js-snackbar__icon')

        switch (_Options.icon) {
          case 'exclamation':
          case 'warn':
          case 'danger':
            icon.innerText = '!'
            break

          case 'info':
          case 'question':
          case 'question-mark':
            icon.innerText = '?'
            break

          case 'plus':
          case 'add':
            icon.innerText = '+'
            break

          default:
            if (_Options.icon.length > 1) {
              console.warn('Invalid icon character provided: ', _Options.icon)
            }

            icon.innerText = _Options.icon.substr(0, 1)
            break
        }

        element.appendChild(icon)
      }
    }

    function insertMessageTo (element) {
      _MessageWrapper = document.createElement('div')

      _MessageWrapper.classList.add('js-snackbar__message-wrapper')

      _Message = document.createElement('span')

      _Message.classList.add('js-snackbar__message')

      _Message.innerHTML = _Options.message

      _MessageWrapper.appendChild(_Message)

      element.appendChild(_MessageWrapper)
    }

    function addActionsTo (element) {
      if (typeof _Options.actions !== 'object') {
        return
      }

      for (var i = 0; i < _Options.actions.length; i++) {
        addAction(element, _Options.actions[i])
      }

      function addAction (element, action) {
        var button = document.createElement('span')
        button.classList.add('js-snackbar__action')
        button.textContent = action.text

        if (typeof action.function === 'function') {
          if (action.dismiss === true) {
            button.onclick = function () {
              action.function()

              _This.Close()
            }
          } else {
            button.onclick = action.function
          }
        } else {
          button.onclick = _This.Close
        }

        element.appendChild(button)
      }
    }

    function addDismissButtonTo (element) {
      if (!_Options.dismissible) {
        return
      }

      var closeButton = document.createElement('span')
      closeButton.classList.add('js-snackbar__close')
      closeButton.innerText = '\u00D7'
      closeButton.onclick = _This.Close
      element.appendChild(closeButton)
    }

    function setWidth (element) {
      if (!_Options.width) return
      element.style.width = _Options.width
    }

    function setSpeed (element) {
      const { speed } = _Options

      switch (typeof speed) {
        case 'number':
          element.style.transitionDuration = speed + 'ms'
          break

        case 'string':
          element.style.transitionDuration = speed
          break
      }
    }
  }

  function _getPositionClass () {
    switch (_Options.position) {
      case 'bl':
        return 'js-snackbar-container--bottom-left'

      case 'tl':
        return 'js-snackbar-container--top-left'

      case 'tr':
        return 'js-snackbar-container--top-right'

      case 'tc':
      case 'tm':
        return 'js-snackbar-container--top-center'

      case 'bc':
      case 'bm':
        return 'js-snackbar-container--bottom-center'

      default:
        return 'js-snackbar-container--bottom-right'
    }
  }

  this.Open = function () {
    var contentHeight = getMessageHeight()
    _Element.style.height = contentHeight + 'px'
    _Element.style.opacity = 1
    _Element.style.marginTop = '5px'
    _Element.style.marginBottom = '5px'

    _Element.addEventListener('transitioned', function () {
      _Element.removeEventListener('transitioned', arguments.callee)

      _Element.style.height = null
    })

    function getMessageHeight () {
      const wrapperStyles = window.getComputedStyle(_MessageWrapper)
      return (
        _Message.scrollHeight +
        parseFloat(wrapperStyles.getPropertyValue('padding-top')) +
        parseFloat(wrapperStyles.getPropertyValue('padding-bottom'))
      )
    }
  }

  this.Close = function () {
    if (_Interval) clearInterval(_Interval)
    var snackbarHeight = _Element.scrollHeight // get the auto height as a px value

    var snackbarTransitions = _Element.style.transition
    _Element.style.transition = ''
    requestAnimationFrame(function () {
      _Element.style.height = snackbarHeight + 'px' // set the auto height to the px height

      _Element.style.opacity = 1
      _Element.style.marginTop = '0px'
      _Element.style.marginBottom = '0px'
      _Element.style.transition = snackbarTransitions
      requestAnimationFrame(function () {
        _Element.style.height = '0px'
        _Element.style.opacity = 0
      })
    })
    setTimeout(function () {
      _Container.removeChild(_Element)
    }, 1000)
  }

  _create()

  _This.Open()
}

if (typeof module !== 'undefined') {
  module.exports = SnackBar
}
