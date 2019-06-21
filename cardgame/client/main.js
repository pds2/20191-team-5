//TODO: strip script tags from literals

const handDragHandler = ev => {
    ev.dataTransfer.setData("text/plain", ev.currentTarget.props.id);
    ev.dropEffect = "move";
};

const testCards = []

const repeatElements = (elementTemplate, propsArray = []) => {
    return propsArray.map(propsEl => elementTemplate(propsEl));
};

/**
 * 
 * @param {HTMLElement} element 
 * @param {HTMLCollection} newElements 
 */
const refreshInternalElements = (element, newElements) => {
    while (element.firstChild) element.removeChild(element.firstChild);
    newElements.forEach(newEl => element.appendChild(newEl));
};

const CardElementTemplate = (props = {}) => {
    let card = document.createElement('div');
    card.classList.add('card-root');
    card.classList.add(props.type);
    card.addEventListener('dragstart', handDragHandler);
    card.props = props;
    console.log(props.imgPath);
    card.innerHTML = `
            <img/>
            <div class="atkdef-container">
                <span>${props.atk}</span>
                <span>${props.def}</span>
            </div>
            <div class="description-container">
                <span>${props.description}</span>
            </div>
        `;
    card.firstElementChild.src = props.imgPath;
    return card;
}

const EnemyCardTemplate = (props = {}) => {
    let card = document.createElement('div');
    card.classList.add('enemy-card-root');
    card.props = props;
    card.innerHTML = `
            <img/>
            <div class="atkdef-container">
                <span>${props.atk}</span>
                <span>${props.def}</span>
            </div>
        `;
    card.firstElementChild.src = props.imgPath;
    card.addEventListener('dragover', ev => {
        ev.preventDefault();
        ev.dataTransfer.dropEffect = "move"
    });
    card.addEventListener('drop', ev => {
        ev.preventDefault();
        let data = ev.dataTransfer.getData("text");
        let attacker = window.engine.ownBoardCards.find(card => card.id == data);
        performAttack(attacker.props, ev.target.parentElement.props);
        // playCard()
    });
    return card;
};

// const HandTemplate();

const playCard = () => {
    // do a request to notify the server
};

const performAttack = () => {

};

globalIDGenerator = 0;

const cardFromCppDescriptor = (cardDescriptor, serverIP, index) => {
    const type = cardDescriptor.includes("atk:") ? "monsters" : "magics";
    const name = cardDescriptor.split(",")[0];
    let cardObject = {
        imgPath: `${serverIP}/assets/img/${type}/${name}.png`,
        atk: null,
        def: null,
        id: ++globalIDGenerator,
        name: name,
        type: type,
        index: index
    };
    if(type === 'monsters'){
        const props = cardDescriptor.split(',').pop().split(' ');
        cardObject.atk = props[1].substr(4);
        cardObject.def = props[2].substr(4);
    } else if(type === 'magics') {
        cardObject.description = cardDescriptor.split(",")[1];
    }
    return cardObject;
};

errorCount = 0;
const GameEngine = function () {
    let __handCards = testCards;
    let __enemyHandCards = [];
    let __enemyBoardCards = [];
    let __ownBoardCards = [];
    let gameRoot = document.querySelector('.game-root');
    let playAreaIndicator = document.querySelector('.play-area-indicator');
    let enemyPlayArea = document.querySelector('.board .enemy-cards');
    let handElement = document.querySelector('.hand-container');
    let ownBoardCards = document.querySelector('.own-cards');
    let enemyHandElement = document.querySelector('.enemy-hand-container');
    refreshInternalElements(handElement, repeatElements(CardElementTemplate, __handCards));
    refreshInternalElements(enemyHandElement, repeatElements(EnemyCardTemplate, [{}, {}]));
    refreshInternalElements(enemyPlayArea, repeatElements(EnemyCardTemplate, testCards.slice(0, 2)));
    Object.defineProperty(this, 'handCards', {
        get: () => __handCards,
        set: function (newCards) {
            __handCards = newCards;
            refreshInternalElements(handElement, repeatElements(CardElementTemplate, newCards));
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(this, 'enemyHandCards', {
        get: () => __enemyHandCards,
        set: function (newCards) {
            __enemyHandCards = newCards;
            refreshInternalElements(enemyHandElement, repeatElements(CardElementTemplate, newCards));
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(this, 'enemyBoardCards', {
        get: () => __enemyBoardCards,
        set: function (newCards) {
            __enemyBoardCards = newCards;
            refreshInternalElements(enemyPlayArea, repeatElements(CardElementTemplate, newCards));
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(this, 'ownBoardCards', {
        get: () => __ownBoardCards,
        set: function (newCards) {
            __ownBoardCards = newCards;
            refreshInternalElements(ownBoardCards, repeatElements(CardElementTemplate, newCards));
        },
        enumerable: true,
        configurable: true
    });

    playAreaIndicator.addEventListener('dragover', ev => {
        ev.preventDefault();
        ev.dataTransfer.dropEffect = "move"
    });
    playAreaIndicator.addEventListener('drop', ev => {
        ev.preventDefault();
        let data = ev.dataTransfer.getData("text");
        let targetCard = __handCards.find(card => card.id == data);
        if (targetCard && targetCard.type === "monsters" && this.turnOwner === "self") {
            engine.ownBoardCards = __ownBoardCards.concat(targetCard);
            engine.handCards = __handCards.filter(card => card.id !== targetCard.id);
            this.summon(targetCard.index);
        }
    });

    let intervalId;
    let listeners = {};
    listeners["END"] = () => clearInterval(intervalId);
    listeners[""] = () => {}; //idle
    listeners["ENEMYSUMMONEDMONSTER"] = () => {
        this.fetchField("enemy").then(cardDescriptorString => {
            let cardStrings = cardDescriptorString.split("|");
            cardStrings.pop();
            let cardObjects = cardStrings.map((cardStr, i) => cardFromCppDescriptor(cardStr, this.serverIP, i));
            this.enemyBoardCards = cardObjects;
        });
    };
    listeners["ENEMYCONNECTED"] = () => {
        document.body.className = "game-running";
        this.fetchHandCards().then(cardDescriptorString => {
            let cardStrings = cardDescriptorString.split("|");
            cardStrings.pop();
            let cardObjects = cardStrings.map((cardStr, i) => cardFromCppDescriptor(cardStr, this.serverIP, i));
            this.handCards = cardObjects;
            this.turnOwner = cardObjects.length === 4 ? "self" : "enemy";
        });
    }

    const _fireEvents = (eventEncodedString) => {
        const events = eventEncodedString.split("|");
        events.forEach(eventString => {
            const eventSplited = eventString.split(",");
            const eventName = eventSplited[0];
            listeners[eventName](eventSplited);
        });
    };

    this.listen = () => {
        intervalId = setInterval(() => {
            fetch(this.serverIP + "/events", {
                method: "POST",
                body: `playerId=${this.playerID}`
            }).then(response => {
                response.text().then(events => {
                    _fireEvents(events);
                });
            }).catch(() => {
                alert("Falha na conexão com o servidor");
                if (++errorCount > 2) {
                    location.reload();
                }
            });
        }, 3000);
    };

    this.onEnemySpellPlayed = () => {};

    this.onEnemyMonsterSummoned = () => {};

    this.fetchHandCards = () => {
        return fetch(this.serverIP + "/getHand", {
            method: "POST",
            body: `playerId=${this.playerID}`
        }).then(response => {
            return response.text();
        }).catch(() => {
            alert("Falha na conexão com o servidor");
            if (++errorCount > 3) {
                location.reload();
            }
        });
    };

    this.summon = (cardIndex) => {
        return fetch(this.serverIP + "/summon", {
            method: "POST",
            body: `playerId=${this.playerID},index=${cardIndex}`
        }).then(response => {
            return response.text();
        }).catch(() => {
            alert("Falha na conexão com o servidor");
            if (++errorCount > 3) {
                location.reload();
            }
        });
    };

    /**
     * @param {String} which self or enemy
     */
    this.fetchField = (which = "self") => {
        return fetch(this.serverIP + "/getField", {
            method: "POST",
            body: `playerId=${this.playerID},which=${which}`
        }).then(response => {
            return response.text();
        }).catch(() => {
            alert("Falha na conexão com o servidor");
            if (++errorCount > 3) {
                location.reload();
            }
        });
    };
};
// http://3.83.190.4:8082
window.initSession = () => {
    let serverIP = document.querySelector('#server-address').value;
    if (serverIP && serverIP !== "") {
        fetch(serverIP + "/join", {
            method: "POST"
        }).then(response => {
            window.engine.serverIP = serverIP;
            response.text().then(content => {
                if (content && content !== "") {
                    window.engine.playerID = content;
                    window.engine.listen();
                } else {
                    alert("Jogo cheio. Reinicie o servidor");
                }
            });
        }).catch(() => {
            alert("Falha na conexão com o servidor");
        });
    }
};

window.engine = new GameEngine();