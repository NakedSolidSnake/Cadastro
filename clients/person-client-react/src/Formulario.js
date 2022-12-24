function Formulario ({botao, onType, onPost, object, cancel, onDelete, onUpdate}) {
    return (
        <form>
            <input type='text'   onChange={onType} value={object.name} name='name'    placeholder="Name"    className="form-control"/>
            <input type='text'   onChange={onType} value={object.address} name='address' placeholder="Address" className="form-control"/>
            <input type='number' onChange={onType} value={object.age} name='age'     placeholder="Age"     className="form-control"/>

            {
                botao ? 
                <input type='button' value="Cadastrar" onClick={onPost} className="btn btn-primary"/>
                :
                <div>
                    <input type='button' onClick={onUpdate} value="Alterar" className="btn btn-warning"/>
                    <input type='button' onClick={onDelete} value="Remover" className="btn btn-danger"/>
                    <input type='button' onClick={cancel} value="Cancelar" className="btn btn-secondary"/>
                </div>
            }
            
        </form>
    )
}

export default Formulario;